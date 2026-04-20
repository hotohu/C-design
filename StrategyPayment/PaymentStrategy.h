#pragma once

#include <string>
#include <memory>

#include "PaymentData.h"

class PaymentStrategy;
using PaymentStrategyPtr = std::unique_ptr<PaymentStrategy>;

enum class PaymentType
{
    CreditCard,
    Crypto,
    Alipay
};

const char* PaymentTypeToString(PaymentType type);

class PaymentError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class CurrencyError : public PaymentError {
public:
    using PaymentError::PaymentError;
};

class BalanceExceededError : public PaymentError {
public:
    using PaymentError::PaymentError;
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
    virtual void MakePayment(const PaymentRequest& request, PaymentData& iData) const = 0;
    virtual ~PaymentStrategy() = default;
};

class CreditCardStrategy final : public PaymentStrategy
{
public:
    void MakePayment(const PaymentRequest& request, PaymentData& iData) const override;
};

class CryptoStrategy : public PaymentStrategy
{
public:
    void MakePayment(const PaymentRequest& request, PaymentData& iData) const override;
};

