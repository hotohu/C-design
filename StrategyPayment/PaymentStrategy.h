#pragma once

#include <string>
#include <memory>

class PaymentStrategy;
using PaymentStrategyPtr = std::unique_ptr<PaymentStrategy>;

enum class PaymentType
{
    CreditCard,
    Crypto
};

struct PaymentRequest
{
    PaymentType type;
    double amount;
    std::string currency;
};

class PaymentStrategy 
{
public:
    virtual void MakePayment(const PaymentRequest& request) = 0;
    virtual ~PaymentStrategy() = default;
};

class CreditCardStrategy final : public PaymentStrategy
{
public:
    void MakePayment(const PaymentRequest& request) override;
    
private:
    double _limit = 1000;
    std::string _currency = "USD";
};


class CryptoStrategy : public PaymentStrategy
{
public:
    void MakePayment(const PaymentRequest& request) override;

private:
    double _balance = 0.8;
    double _currentFee = 0.00001;
    std::string _currency = "BTC";
};

