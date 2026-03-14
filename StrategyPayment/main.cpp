#include <iostream>

#include "PaymentProcessor.h"

int main() {
    PaymentRequest request{PaymentType::CreditCard, 100, ""};

    PaymentProcessor processor;
    processor.process(request);
}
