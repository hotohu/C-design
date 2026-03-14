#pragma once

#include <string>

enum class PaymentType
{
    CreditCard,
    PayPal,
    Crypto,
    BankTransfer
};

struct PaymentRequest
{
    PaymentType type;
    double amount;
    std::string currency;
};

enum class PaymentResult
{
    OK,
    FAIL,
};

class PaymentStrategy 
{
public:
    PaymentResult MakePayment();
    virtual ~PaymentStrategy() {};

private:
    virtual PaymentResult MakePaymentImpl() = 0;
};

class CreditCardStrategy : public PaymentStrategy
{
private:
    virtual PaymentResult MakePaymentImpl();
};