#include "PaymentStrategy.h"

#include <iostream>

PaymentResult PaymentStrategy::MakePayment() {
    PaymentResult res = MakePaymentImpl();
    return res;
}

PaymentResult CreditCardStrategy::MakePaymentImpl() {
    PaymentResult res = PaymentResult::OK;
    std::cout << "Credit card payment" << std::endl;
    return res;
}
