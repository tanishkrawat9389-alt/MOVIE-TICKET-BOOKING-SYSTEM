#include <vector>
#include <string>
#include "05_Show.cpp"
#include "07_Customer.cpp"
using namespace std;

class Booking {
public:
    enum class Status { PENDING, CONFIRMED, FAILED, CANCELLED };
private:
    static int nextBookingId;
    string bookingId;
    Customer* customer;
    Show* show;
    vector<ShowSeat*> seats;
    double bookingAmount;
    Status status;
public:
    Booking(Customer* customer, Show* show, const vector<ShowSeat*>& seats, double amount)
        : customer(customer), show(show), seats(seats), bookingAmount(amount), status(Status::PENDING) {
        bookingId = "BK" + to_string(nextBookingId++);
    }
    string getBookingId() const { return bookingId; }
    Customer* getCustomer() const { return customer; }
    Show* getShow() const { return show; }
    const vector<ShowSeat*>& getSeats() const { return seats; }
    double getAmount() const { return bookingAmount; }
    Status getStatus() const { return status; }
    void confirm() { status = Status::CONFIRMED; }
    void fail() { status = Status::FAILED; }
    void cancel() { status = Status::CANCELLED; }
};

int Booking::nextBookingId = 1001; // Static member creates unique booking IDs.
