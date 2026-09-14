#pragma once
#include <string>
#include "02_Seat.cpp"
using namespace std;

class ShowSeat {
public:
    enum class Status { AVAILABLE, BOOKED };
private:
    Seat* seat;
    Status status;
public:
    explicit ShowSeat(Seat* seat) : seat(seat), status(Status::AVAILABLE) {}
    Seat* getSeat() const { return seat; }
    Status getStatus() const { return status; }
    bool isAvailable() const { return status == Status::AVAILABLE; }
    bool bookSeat() {
        if (!isAvailable()) return false;
        status = Status::BOOKED;
        return true;
    }
    void cancelSeat() { status = Status::AVAILABLE; }
};
