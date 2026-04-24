#include <iostream>

#include "PaymentProcessor.h"
#include "PaymentError.h"


void PaymentMakeAttemptsAPI(PaymentProcessor& iProcessor, 
    std::vector<std::pair<PaymentRequest, PaymentContext&>>& iAttempts) {
    for (auto& attempt : iAttempts) {
        std::cerr << "Starting attempt" << std::endl;
        try {
            iProcessor.process(attempt.first, attempt.second);
            break;
        } catch(PaymentError& err) {
            std::cerr << "Attempt failed: " << err.what() << std::endl;
        }
        std::cerr << "Finished attempt" << std::endl;
    }
}

void PaymentProcessorTestAPI() 
{
    PaymentProcessor processor;
    processor.registerStrategy(PaymentType::CreditCard, std::make_unique<CreditCardStrategy>());
    processor.registerStrategy(PaymentType::Crypto, std::make_unique<CryptoStrategy>());

    try {
        processor.unregisterStrategy(PaymentType::Alipay);
    } catch(PaymentError& err) {
        std::cerr << err.what() << std::endl;
    }

    PaymentContext data;

    CreditCardPaymentData ccData;
    ccData.limit = 200;

    CryptoPaymentData crData;
    crData.balance = 0.001;
    crData.feeInPercent = 5;

    std::vector<std::pair<PaymentRequest, PaymentContext&>> attemptsAlipay = {
        { PaymentRequest{ PaymentType::Alipay, 100, "CNY" }, data},
        { PaymentRequest{ PaymentType::CreditCard, 100 * 0.15, "USD" }, ccData},
    };

    PaymentMakeAttemptsAPI(processor, attemptsAlipay);

    std::vector<std::pair<PaymentRequest, PaymentContext&>> attemptsCrypto = {
        { PaymentRequest{ PaymentType::Crypto, 0.014, "BTC" }, crData},
        { PaymentRequest{ PaymentType::CreditCard, 0.014 * 77673, "USD" }, ccData},
    };

    PaymentMakeAttemptsAPI(processor, attemptsCrypto);
}

int main() 
{    
    try {
        PaymentProcessorTestAPI();
    } catch(std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }
}
