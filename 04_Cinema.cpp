#include <vector>
#include "03_Screen.cpp"
using namespace std;

class Cinema {
private:
    string name;
    vector<Screen> screens; // Composition: Cinema owns its screens.
public:
    Cinema(string name) : name(name) { screens.emplace_back(1); screens.emplace_back(2); }
    string getName() const { return name; }
    vector<Screen>& getScreens() { return screens; }
    const vector<Screen>& getScreens() const { return screens; }
};
