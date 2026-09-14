#include <iostream>
#include "13_BookingService.cpp"
using namespace std;

int main() {
    BookingService bookingService;
    Customer customer("Tanishk Rawat", "9999999999");

    while (true) {
        cout << "\n===== MOVIE TICKET BOOKING =====\n";
        cout << "1. Movies  2. Book  3. Cancel  4. My tickets  0. Exit\n";
        cout << "Choose: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid menu choice.\n";
            continue;
        }
        cin.ignore(10000, '\n');
        if (choice == 1) bookingService.listMovies();
        else if (choice == 2) bookingService.book(customer);
        else if (choice == 3) bookingService.cancelBooking();
        else if (choice == 4) bookingService.myTickets();
        else if (choice == 0) { cout << "Goodbye!\n"; break; }
        else cout << "Invalid menu choice.\n";
    }
    return 0;
}
