#include <iostream>
#include <functional>
#include <map>

#include "PaymentProcessor.h"
#include "PaymentStrategyLogger.h"

int main() {
    PaymentRequest request{PaymentType::CreditCard, 100000, "USD"};

    std::map<PaymentType, std::function<PaymentStrategyPtr()>> strategyCreator = {
        {PaymentType::CreditCard, []() {
            return std::make_unique<CreditCardStrategy>();
        }}
    };

    PaymentStrategyPtr strategy(strategyCreator[request.type]());
    PaymentStrategyPtr loggerWrapper = std::make_unique<PaymentStrategyLogger>(std::move(strategy));

    PaymentProcessor processor(std::move(loggerWrapper));
    processor.process(request);
}
