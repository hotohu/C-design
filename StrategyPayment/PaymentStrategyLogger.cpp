#include <iostream>

#include "PaymentStrategyLogger.h"

PaymentStrategyLogger::PaymentStrategyLogger(PaymentStrategyPtr iStrategy) 
: _strategy(std::move(iStrategy))
{}

void PaymentStrategyLogger::MakePayment(const PaymentRequest& request) 
{
    std::cerr << "Starting the payment - " << PaymentTypeToString(request.type) << std::endl;
    _strategy->MakePayment(request);
    std::cerr << "Payment completed - " << PaymentTypeToString(request.type) << std::endl;
}
