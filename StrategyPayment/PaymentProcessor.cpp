#include "PaymentProcessor.h"

PaymentResult PaymentProcessor::process(const PaymentRequest& request)
{
    CreditCardStrategy strategy;
    PaymentResult res = strategy.MakePayment();
    return res;
}
