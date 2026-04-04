#include "PaymentStrategy.h"

#include <iostream>

CreditCardStrategy::CreditCardStrategy()
: _service(new MockBankService())
{
}

PaymentResult CreditCardStrategy::MakePayment(const PaymentRequest& request) 
{
    if (_service->GetCurrency() != request.currency) {
        return PaymentResult::FAIL;
    }

    if (_service->GetLimit() < request.amount) {
        return PaymentResult::FAIL;
    }

    _service->ProcessTransaction(request.amount);

    return PaymentResult::OK;
}

void MockBankService::ProcessTransaction(double amount)
{
    if (_limit - amount > 0) {
        std::cout << "Transaction was succesfully processed" << std::endl;
        _limit -= amount;
        return;
    }

    std::cout << "Transaction was not processed" << std::endl;
}

