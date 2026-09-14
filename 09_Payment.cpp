class Payment {
public:
    virtual ~Payment() = default;
    virtual bool pay(double amount) = 0; // Abstraction: payment contract.
};
