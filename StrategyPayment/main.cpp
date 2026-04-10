#include <iostream>
#include <functional>
#include <map>
#include <exception>

#include "PaymentProcessor.h"
#include "PaymentStrategyLogger.h"


// какие ошибки могут быть ?
// нет необходимой стратегии
// не хватило денег на счете
// все остальные исключения

// что будет
// не прерываем программу
// пытаемся сделать другой платеж 

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
    if (!strategyCreator.count(iRequest.type))
        throw std::runtime_error("This strategy wasn't supported");

    PaymentStrategyPtr strategy(strategyCreator[iRequest.type]());
    PaymentStrategyPtr loggerWrapper = std::make_unique<PaymentStrategyLogger>(std::move(strategy));
    
    PaymentProcessor processor(std::move(loggerWrapper));
    processor.process(iRequest);
}

int main() {
    PaymentRequest requestCreditCard{PaymentType::CreditCard, 100000, "USD"};
    PaymentRequest requestCrypto{PaymentType::Crypto, 0.014, "BTC"};

    try {
        ProcessRequestByStrategy(requestCreditCard);
        ProcessRequestByStrategy(requestCrypto);
    } catch(std::exception& iError) {
        std::cerr << iError.what() << std::endl;
    }
}
