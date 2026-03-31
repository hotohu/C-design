#include <iostream>
#include <functional>
#include <map>

#include "PaymentProcessor.h"

int main() {
    PaymentRequest request{PaymentType::CreditCard, 100000, "USD"};

    std::map<PaymentType, std::function<PaymentStrategyPtr()>> strategyCreator = {
        {PaymentType::CreditCard, []() {
            return std::make_unique<CreditCardStrategy>();
        }}
    };

    PaymentProcessor processor(strategyCreator[request.type]());
    processor.process(request);
}
