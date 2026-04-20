#include <iostream>

#include "PaymentProcessor.h"
#include "PaymentError.h"

void ProcessRequestByStrategy(PaymentProcessor& iProcessor, const PaymentRequest& iRequest, PaymentContext& iData)
{
    try {
        return iProcessor.process(iRequest, iData);
    } catch (const PaymentDeclinedError& iError) {
        return iProcessor.processDefault(iRequest, iData);
    }
}

int main() 
{    
    PaymentProcessor processor;
    processor.registerDefaultStrategy(PaymentType::CreditCard, std::make_unique<CreditCardStrategy>());
    processor.registerStrategy(PaymentType::Crypto, std::make_unique<CryptoStrategy>());

    try {
        processor.unregisterStrategy(PaymentType::Alipay);
    } catch(PaymentResolvingError& err) {
        std::cerr << err.what() << std::endl;
    }

    PaymentRequest requestAlipay{PaymentType::Alipay};
    PaymentRequest requestCreditCard{PaymentType::CreditCard, 100000, "USD"};
    PaymentRequest requestCrypto{PaymentType::Crypto, 0.014, "BTC"};

    PaymentContext data;

    CreditCardPaymentData ccData;
    ccData.limit = 200;

    CryptoPaymentData crData;
    crData.balance = 0.001;
    crData.feeInPercent = 5;

    try {
        ProcessRequestByStrategy(processor, requestAlipay, data);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }

    try {
        ProcessRequestByStrategy(processor, requestCreditCard, ccData);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }
    
    //ProcessRequestByStrategy(processor, requestCrypto, crData);
}
