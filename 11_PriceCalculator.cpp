#include <vector>
#include "06_ShowSeat.cpp"
using namespace std;

class PriceCalculator {
public:
    double calculate(const vector<ShowSeat*>& seats) const {
        double total = 0;
        for (const auto* showSeat : seats) total += showSeat->getSeat()->getPrice();
        return total;
    }
};
