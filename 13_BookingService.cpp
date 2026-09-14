#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include "05_Show.cpp"
#include "08_Booking.cpp"
#include "10_PaymentTypes.cpp"
#include "11_PriceCalculator.cpp"
#include "12_TicketPrinter.cpp"
using namespace std;

class BookingService {
private:
    Cinema cinema;
    vector<Movie> movies;
    vector<Show> shows;
    vector<unique_ptr<Booking>> bookings;
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;
public:
    BookingService() : cinema("PVR Cinema") { seedData(); }
    void listMovies() const {
        cout << "\n--- MOVIES CURRENTLY PLAYING ---\n";
        for (size_t i = 0; i < movies.size(); ++i)
            cout << "[" << i + 1 << "] " << movies[i].getTitle() << " | " << movies[i].getLanguage() << " | " << movies[i].getDuration() << " min\n";
    }
    void listShows(int movieChoice) const {
        if (!validMovie(movieChoice)) { cout << "Invalid movie choice.\n"; return; }
        const Movie* movie = &movies[movieChoice - 1];
        cout << "\nShows for " << movie->getTitle() << ":\n";
        for (size_t i = 0; i < shows.size(); ++i)
            if (shows[i].getMovie() == movie)
                cout << "[" << i + 1 << "] Screen-" << shows[i].getScreen()->getScreenNumber() << " | " << shows[i].getStartTime() << '\n';
    }
    void showSeats(int showChoice) const {
        const Show* show = getShow(showChoice);
        if (!show) { cout << "Invalid show choice.\n"; return; }
        show->displaySeats();
    }
    void book(Customer& customer) {
        listMovies();
        int movieChoice = readInt("Choose movie: ");
        if (!validMovie(movieChoice)) { cout << "Invalid movie choice.\n"; return; }
        listShows(movieChoice);
        int showChoice = readInt("Choose show: ");
        Show* show = getShow(showChoice);
        if (!show || show->getMovie() != &movies[movieChoice - 1]) { cout << "Invalid show choice.\n"; return; }
        show->displaySeats();
        vector<ShowSeat*> selected = selectSeats(*show, readLine("Enter seat number(s), separated by spaces: "));
        if (selected.empty()) return;
        double total = priceCalculator.calculate(selected);
        cout << "TOTAL: Rs." << total << '\n';
        bookings.push_back(make_unique<Booking>(&customer, show, selected, total));
        Booking* booking = bookings.back().get();
        unique_ptr<Payment> payment = choosePayment();
        // Dependency Inversion + Runtime Polymorphism: the flow depends on abstract Payment.
        if (!payment->pay(total)) {
            booking->fail();
            cout << "Payment failed. Booking NOT confirmed; seats remain AVAILABLE.\n";
            return;
        }
        for (auto* seat : selected) seat->bookSeat();
        booking->confirm();
        cout << "Payment successful. Booking confirmed.\n";
        ticketPrinter.printTicket(*booking);
    }
    void cancelBooking() {
        string id = readLine("Enter booking ID: ");
        for (auto& booking : bookings) {
            if (booking->getBookingId() == id && booking->getStatus() == Booking::Status::CONFIRMED) {
                for (auto* seat : booking->getSeats()) seat->cancelSeat();
                booking->cancel();
                cout << "Booking cancelled. Seats are AVAILABLE again.\n";
                return;
            }
        }
        cout << "Active booking not found.\n";
    }
    void myTickets() const {
        bool found = false;
        for (const auto& booking : bookings) if (booking->getStatus() == Booking::Status::CONFIRMED) {
            ticketPrinter.printTicket(*booking); found = true;
        }
        if (!found) cout << "No active tickets.\n";
    }
private:
    void seedData() {
        movies.emplace_back("3 Idiots", "Hindi", 170);
        movies.emplace_back("Interstellar", "English", 169);
        movies.emplace_back("Inception", "English", 148);
        auto& screens = cinema.getScreens();
        shows.emplace_back(&movies[0], &screens[0], "06:00 PM");
        shows.emplace_back(&movies[0], &screens[1], "09:00 PM");
        shows.emplace_back(&movies[1], &screens[0], "05:30 PM");
        shows.emplace_back(&movies[2], &screens[1], "08:30 PM");
    }
    bool validMovie(int choice) const { return choice >= 1 && choice <= static_cast<int>(movies.size()); }
    Show* getShow(int choice) { if (choice < 1 || choice > static_cast<int>(shows.size())) return nullptr; return &shows[choice - 1]; }
    const Show* getShow(int choice) const { if (choice < 1 || choice > static_cast<int>(shows.size())) return nullptr; return &shows[choice - 1]; }
    vector<ShowSeat*> selectSeats(Show& show, const string& input) {
        vector<ShowSeat*> selected;
        istringstream stream(input); string seatNumber;
        while (stream >> seatNumber) {
            ShowSeat* seat = show.findShowSeat(seatNumber);
            if (!seat) { cout << "Invalid seat: " << seatNumber << '\n'; return {}; }
            if (!seat->isAvailable()) { cout << "Seat " << seatNumber << " is already BOOKED. Nothing changed.\n"; return {}; }
            selected.push_back(seat);
        }
        return selected;
    }
    unique_ptr<Payment> choosePayment() {
        int method = readInt("Pay by: 1.UPI  2.Card  3.Cash: ");
        if (method == 1) return make_unique<UpiPayment>(readLine("Enter UPI ID (type fail to simulate failure): "));
        if (method == 2) return make_unique<CardPayment>(readLine("Enter card reference (type fail to simulate failure): "));
        if (method == 3) return make_unique<CashPayment>();
        cout << "Invalid payment method.\n"; return make_unique<UpiPayment>("fail");
    }
    static int readInt(const string& prompt) {
        cout << prompt; int value;
        if (!(cin >> value)) { cin.clear(); cin.ignore(10000, '\n'); return -1; }
        cin.ignore(10000, '\n'); return value;
    }
    static string readLine(const string& prompt) { cout << prompt; string value; getline(cin, value); return value; }
};
