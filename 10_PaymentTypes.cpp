#include <string>
#include "09_Payment.cpp"
using namespace std;

class UpiPayment : public Payment {
private:
    string upiId;
public:
    explicit UpiPayment(string upiId) : upiId(upiId) {}
    bool pay(double amount) override { return amount > 0 && upiId != "fail"; }
};

class CardPayment : public Payment {
private:
    string cardNumber;
public:
    explicit CardPayment(string cardNumber) : cardNumber(cardNumber) {}
    bool pay(double amount) override { return amount > 0 && cardNumber != "fail"; }
};

class CashPayment : public Payment {
public:
    bool pay(double amount) override { return amount > 0; }
};
