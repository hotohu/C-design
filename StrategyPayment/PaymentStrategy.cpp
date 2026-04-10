#include "PaymentStrategy.h"

const char* PaymentTypeToString(PaymentType type) {
    switch (type) {
        case PaymentType::CreditCard: return "CreditCard";
        case PaymentType::Crypto: return "Crypto";
        case PaymentType::Alipay: return "Alipay";
        default: return "Unknown";
    }
}

void CreditCardStrategy::MakePayment(const PaymentRequest& request) 
{
    if (_currency != request.currency) {
        throw std::runtime_error("Currency of the request isn't eligible for this payment");
    }

    if (request.amount > _limit) {
        throw std::runtime_error("Limit of the credit card less than amount");
    }

    _limit -= request.amount;
}

void CryptoStrategy::MakePayment(const PaymentRequest& request) 
{
    if (_currency != request.currency) {
        throw std::runtime_error("Currency of the request isn't eligible for this payment");
    }

    if (request.amount > _currentFee + _balance) {
        throw std::runtime_error("Balance of the wallet less than amount and fee");
    }

    double requiredPayment = _currentFee + _balance;
    _balance -= requiredPayment;
}
