#include "09_Payment.cpp"

class UpiPayment : public Payment {
public:
    bool pay(double amount) override { return amount > 0; }
};

class CardPayment : public Payment {
public:
    bool pay(double amount) override { return amount > 0; }
};

class CashPayment : public Payment {
public:
    bool pay(double amount) override { return amount > 0; }
};
