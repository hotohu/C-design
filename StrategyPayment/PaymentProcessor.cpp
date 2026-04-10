
#include <iostream>
#include "PaymentProcessor.h"

PaymentProcessor::PaymentProcessor(PaymentStrategyPtr iStrategy) : _strategy(std::move(iStrategy)) 
{}

void PaymentProcessor::process(const PaymentRequest& request) const
{
    _strategy->MakePayment(request);
}
