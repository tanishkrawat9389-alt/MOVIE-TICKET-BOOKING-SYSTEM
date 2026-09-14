#include <iostream>
#include "08_Booking.cpp"
using namespace std;

class TicketPrinter {
public:
    void printTicket(const Booking& booking) const {
        const Show* show = booking.getShow();
        cout << "\n================ TICKET ================\n";
        cout << "Booking ID : " << booking.getBookingId() << '\n';
        cout << "Movie      : " << show->getMovie()->getTitle() << '\n';
        cout << "Screen     : Screen-" << show->getScreen()->getScreenNumber() << '\n';
        cout << "Time       : " << show->getStartTime() << '\n';
        cout << "Seats      : ";
        for (size_t index = 0; index < booking.getSeats().size(); ++index) {
            if (index) cout << ", ";
            cout << booking.getSeats()[index]->getSeat()->getNumber();
        }
        cout << "\nAmount     : Rs." << booking.getAmount();
        cout << "\nStatus     : CONFIRMED\n";
        cout << "=========================================\n";
    }
};
