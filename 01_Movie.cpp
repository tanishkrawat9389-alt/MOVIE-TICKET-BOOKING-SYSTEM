#include <string>
using namespace std;

class Movie {
private:
    string title;
    string language;
    int durationMinutes;
public:
    Movie(string title, string language, int durationMinutes)
        : title(title), language(language), durationMinutes(durationMinutes) {}
    Movie() : Movie("", "", 0) {} // compile-time polymorphism: overloaded constructor
    string getTitle() const { return title; }
    string getLanguage() const { return language; }
    int getDuration() const { return durationMinutes; }
};
