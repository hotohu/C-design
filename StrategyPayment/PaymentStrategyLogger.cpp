#include <iostream>

#include "PaymentStrategyLogger.h"

PaymentStrategyLogger::PaymentStrategyLogger(PaymentStrategyPtr iStrategy) 
: _strategy(std::move(iStrategy))
{}

void PaymentStrategyLogger::MakePayment(const PaymentRequest& request) 
{
    std::cout << "Try to make payment:" << std::endl;
    _strategy->MakePayment(request);
    std::cout << "Payment was made:" << std::endl;
}
