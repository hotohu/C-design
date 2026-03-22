#include <iostream>

#include "PaymentProcessor.h"

int main() {
    PaymentRequest request{PaymentType::CreditCard, 100000, "USD"};

    PaymentProcessor processor;
    processor.process(request);
}
