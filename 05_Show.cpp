#include <iostream>
#include <vector>
#include "01_Movie.cpp"
#include "04_Cinema.cpp"
#include "06_ShowSeat.cpp"
using namespace std;

class Show {
private:
    Movie* movie;
    Screen* screen;
    string startTime;
    vector<ShowSeat> showSeats;
public:
    Show(Movie* movie, Screen* screen, string startTime)
        : movie(movie), screen(screen), startTime(startTime) { initializeSeats(); }
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getStartTime() const { return startTime; }
    vector<ShowSeat>& getShowSeats() { return showSeats; }
    const vector<ShowSeat>& getShowSeats() const { return showSeats; }
    ShowSeat* findShowSeat(const string& seatNumber) {
        for (auto& showSeat : showSeats)
            if (showSeat.getSeat()->getNumber() == seatNumber) return &showSeat;
        return nullptr;
    }
    void displaySeats() const {
        cout << "\n" << movie->getTitle() << " | Screen-" << screen->getScreenNumber()
             << " | " << startTime << "\n[ ] = AVAILABLE   [X] = BOOKED\n";
        for (const auto& showSeat : showSeats) {
            const Seat* seat = showSeat.getSeat();
            cout << seat->getNumber() << " " << Seat::typeName(seat->getType())
                 << " [" << (showSeat.isAvailable() ? ' ' : 'X') << "]   ";
            if (seat->getNumber().back() == '4') cout << '\n';
        }
    }
private:
    void initializeSeats() {
        for (const auto& seat : screen->getSeats()) showSeats.emplace_back(const_cast<Seat*>(&seat));
    }
};
