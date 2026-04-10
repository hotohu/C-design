#include "PaymentStrategy.h"

#include <iostream>

void CreditCardStrategy::MakePayment(const PaymentRequest& request) 
{
    if (_currency != request.currency) {
        throw std::runtime_error("Currency of request isn't eligible for this payment");
    }

    if (request.amount > _limit) {
        throw std::runtime_error("Limit of credit card less than amount");
    }

    _limit -= request.amount;
}

void CryptoStrategy::MakePayment(const PaymentRequest& request) 
{
    if (_currency != request.currency) {
        throw std::runtime_error("Currency of request isn't eligible for this payment");
    }

    if (request.amount > _currentFee + _balance) {
        throw std::runtime_error("Balance of wallet less than amount and fee");
    }

    double requiredPayment = _currentFee + _balance;
    _balance -= requiredPayment;
}
