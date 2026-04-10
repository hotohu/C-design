#include <iostream>
#include <functional>
#include <map>

#include "PaymentProcessor.h"
#include "PaymentStrategyLogger.h"

static std::map<PaymentType, std::function<PaymentStrategyPtr()>> strategyCreator = {
        {PaymentType::CreditCard, []() {
            return std::make_unique<CreditCardStrategy>();
        }},
        {PaymentType::Crypto, []() {
            return std::make_unique<CryptoStrategy>();
        }}
};

void ProcessRequestByStrategy(const PaymentRequest& iRequest)
{
    try {
        if (!strategyCreator.count(iRequest.type))
            throw std::runtime_error("This strategy wasn't supported - " + std::string(PaymentTypeToString(iRequest.type)));

        PaymentStrategyPtr strategy(strategyCreator[iRequest.type]());
        PaymentStrategyPtr loggerWrapper = std::make_unique<PaymentStrategyLogger>(std::move(strategy));
        
        PaymentProcessor processor(std::move(loggerWrapper));
        processor.process(iRequest);
    } catch(std::exception& iError) {
        std::cerr << iError.what() << std::endl;
    }
}

int main() {
    PaymentRequest requestAlipay{PaymentType::Alipay};
    PaymentRequest requestCreditCard{PaymentType::CreditCard, 100000, "USD"};
    PaymentRequest requestCrypto{PaymentType::Crypto, 0.014, "BTC"};

    ProcessRequestByStrategy(requestAlipay);
    ProcessRequestByStrategy(requestCreditCard);
    ProcessRequestByStrategy(requestCrypto);
}
