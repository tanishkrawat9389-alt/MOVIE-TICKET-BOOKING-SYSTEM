#include <ctime>
#include <vector>
#include "01_Movie.cpp"
#include "04_Cinema.cpp"
using namespace std;

class Show {
private:
    Movie* movie;
    Screen* screen;
    string startTime;
    vector<class ShowSeat> showSeats;
public:
    Show(Movie* movie, Screen* screen, string startTime) : movie(movie), screen(screen), startTime(startTime) {}
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getStartTime() const { return startTime; }
    vector<class ShowSeat>& getShowSeats() { return showSeats; }
    void initializeSeats();
    void displaySeats() const;
    class ShowSeat* findShowSeat(const string& seatNumber);
};
