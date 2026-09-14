#pragma once
#include <string>
using namespace std;

class Seat {
public:
    enum class Type { SILVER, GOLD, PLATINUM };
    static constexpr double SILVER_PRICE = 150.0;
    static constexpr double GOLD_PRICE = 250.0;
    static constexpr double PLATINUM_PRICE = 400.0;
private:
    string number;
    Type type;
public:
    Seat(string number, Type type) : number(number), type(type) {}
    string getNumber() const { return number; }
    Type getType() const { return type; }
    double getPrice() const {
        if (type == Type::SILVER) return SILVER_PRICE;
        if (type == Type::GOLD) return GOLD_PRICE;
        return PLATINUM_PRICE;
    }
    static string typeName(Type type) {
        if (type == Type::SILVER) return "SILVER";
        if (type == Type::GOLD) return "GOLD";
        return "PLATINUM";
    }
};
