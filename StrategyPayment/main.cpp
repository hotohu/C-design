#include <iostream>

#include "PaymentProcessor.h"
#include "PaymentError.h"

int main() 
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

    std::vector<std::pair<PaymentRequest, PaymentContext&>> attempts = {
        { PaymentRequest{ PaymentType::Alipay, 100, "CNY" }, data},
        { PaymentRequest{ PaymentType::CreditCard, 100 * 0.15, "USD" }, ccData},
    };

    for (auto& attempt : attempts) {
        try {
            processor.process(attempt.first, attempt.second);
            break;
        } catch(PaymentError& err) {
            std::cerr << err.what() << std::endl;
        }
    }

    /*PaymentRequest requestCreditCard{PaymentType::CreditCard, 100000, "USD"};
    try {
        processor.process(requestCreditCard, ccData);
    } catch (const PaymentError& err) {
        std::cerr << err.what() << std::endl;
    }

    PaymentRequest requestCrypto{PaymentType::Crypto, 0.014, "BTC"};
    try {
        processor.process(requestCrypto, crData);
    }
    catch (const PaymentDeclinedError& err) {

        // try to make default payment
        PaymentRequest requestCreditCard{PaymentType::CreditCard, requestCrypto.amount*77463, "USD"};
        processor.process(requestCreditCard, ccData);
    }
    catch (const PaymentError& err) {
        std::cerr << err.what() << std::endl;
    }*/

}
