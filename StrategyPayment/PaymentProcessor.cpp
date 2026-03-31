
#include <iostream>
#include "PaymentProcessor.h"

PaymentResult PaymentProcessor::process(const PaymentRequest& request)
{
    PaymentResult res = _strategy->MakePayment(request);

    if (res == PaymentResult::OK) {
        std::cout << "OK" << std::endl;
    }

    if (res == PaymentResult::FAIL) {
        std::cout << "FAIL" << std::endl;
    }

    return res;
}
