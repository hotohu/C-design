#include <iostream>

#include "PaymentProcessor.h"
#include "PaymentData.h"

void ProcessRequestByStrategy(PaymentProcessor& iProcessor, const PaymentRequest& iRequest, PaymentData& iData)
{
    try {
        iProcessor.process(iRequest, iData);
    } catch(const StrategyError& iError) {
        std::cerr << iError.what() << std::endl;
    } catch(const BalanceExceededError& iError) {
        iProcessor.processDefault(iRequest, iData);
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

    PaymentData data;

    CreditCardPaymentData ccData;
    ccData.limit = 200;

    CryptoPaymentData crData;
    crData.balance = 0.001;
    crData.feeInPercent = 5;

    ProcessRequestByStrategy(processor, requestAlipay, data);
    ProcessRequestByStrategy(processor, requestCreditCard, ccData);
    ProcessRequestByStrategy(processor, requestCrypto, crData);
}
