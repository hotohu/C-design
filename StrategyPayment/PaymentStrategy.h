#pragma once

#include <string>
#include <memory>

#include "PaymentContext.h"

class PaymentStrategy;
using PaymentStrategyPtr = std::unique_ptr<PaymentStrategy>;

enum class PaymentType
{
    CreditCard,
    Crypto,
    Alipay
};

const char* PaymentTypeToString(PaymentType type);

struct PaymentRequest
{
    PaymentType type;
    double amount;
    std::string currency;
};

class PaymentStrategy 
{
public:
    virtual void Process(const PaymentRequest& request, PaymentContext& iData) const = 0;
    virtual ~PaymentStrategy() = default;
};

class CreditCardStrategy final : public PaymentStrategy
{
public:
    void Process(const PaymentRequest& request, PaymentContext& iData) const override;
};

class CryptoStrategy final : public PaymentStrategy
{
public:
    void Process(const PaymentRequest& request, PaymentContext& iData) const override;
};

