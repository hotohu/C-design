#include <iostream>

#include "PaymentProcessor.h"
#include "PaymentStrategyLogger.h"

void ProcessRequestByStrategy(PaymentProcessor& iProcessor, const PaymentRequest& iRequest)
{
    try {
        iProcessor.process(iRequest);
    } catch(const StrategyError& iError) {
        std::cerr << iError.what() << std::endl;
    } catch(const BalanceExceededError& iError) {
        iProcessor.processDefault(iRequest);
    }
}

int main() 
{    
    PaymentProcessor processor;
    processor.registerStrategy(PaymentType::CreditCard, std::make_unique<CreditCardStrategy>());
    processor.registerStrategy(PaymentType::Crypto, std::make_unique<CryptoStrategy>());

    PaymentRequest requestAlipay{PaymentType::Alipay};
    PaymentRequest requestCreditCard{PaymentType::CreditCard, 100000, "USD"};
    PaymentRequest requestCrypto{PaymentType::Crypto, 0.014, "BTC"};

    ProcessRequestByStrategy(processor, requestAlipay);
    ProcessRequestByStrategy(processor, requestCreditCard);
    ProcessRequestByStrategy(processor, requestCrypto);
}
