
#include <iostream>
#include "PaymentProcessor.h"

PaymentResult PaymentProcessor::process(const PaymentRequest& request)
{
    CreditCardStrategy strategy;
    PaymentResult res = strategy.MakePayment(request);

    if (res == PaymentResult::OK) {
        std::cout << "OK" << std::endl;
    }

    if (res == PaymentResult::FAIL) {
        std::cout << "FAIL" << std::endl;
    }

    return res;
}
