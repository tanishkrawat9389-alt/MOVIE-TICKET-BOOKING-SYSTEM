#include <string>
#include <vector>
using namespace std;

#include "02_Seat.cpp"

class Screen {
private:
    int screenNumber;
    vector<Seat> seats; // Composition: Screen owns its physical seats.
public:
    Screen(int screenNumber) : screenNumber(screenNumber) { createSeats(); }
    int getScreenNumber() const { return screenNumber; }
    const vector<Seat>& getSeats() const { return seats; }
private:
    void createSeats() {
        for (char row = 'A'; row <= 'C'; ++row) {
            Seat::Type type = row == 'A' ? Seat::Type::SILVER : (row == 'B' ? Seat::Type::GOLD : Seat::Type::PLATINUM);
            for (int number = 1; number <= 4; ++number)
                seats.emplace_back(string(1, row) + to_string(number), type);
        }
    }
};
