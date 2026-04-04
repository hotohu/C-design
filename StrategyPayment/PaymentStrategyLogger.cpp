#include <iostream>

#include "PaymentStrategyLogger.h"

PaymentResult PaymentStrategyLogger::MakePayment(const PaymentRequest& request) 
{
    std::cout << "Try to make payment:" << std::endl;
    PaymentResult res = _strategy->MakePayment(request);
    std::cout << "Payment was made:" << std::endl;

    return res;
}
