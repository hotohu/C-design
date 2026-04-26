#include "PaymentStrategy.h"
#include "PaymentError.h"

const char* PaymentTypeToString(PaymentType type) {
    switch (type) {
        case PaymentType::CreditCard: return "CreditCard";
        case PaymentType::Crypto: return "Crypto";
        case PaymentType::Alipay: return "Alipay";
        default: return "Unknown";
    }
}

void CreditCardStrategy::Process(const PaymentRequest& request, PaymentContext& iData) const
{
    try {
        CreditCardPaymentData& data = dynamic_cast<CreditCardPaymentData&>(iData);
        if (request.amount > data.limit) {
            throw PaymentDeclinedError("Credit card data doesn't have enough limit to process payment");
        }

        data.limit -= request.amount;
    } catch(std::bad_cast& err) {
        throw PaymentDeclinedError("We don't have credit card data-type to process payment");
    }
}


void CryptoStrategy::Process(const PaymentRequest& request, PaymentContext& iData) const
{
    try {
        CryptoPaymentData& data = dynamic_cast<CryptoPaymentData&>(iData);
  
        if (!data.walletValidated) {
            throw PaymentDeclinedError("Crypto data isn't validated");
        }
        
        double fee = (request.amount / 100) * data.feeInPercent;
        const double requiredPayment = fee + request.amount;

        if (requiredPayment > data.balance) {
            throw PaymentDeclinedError("Crypto data doesn't have enough amount to process payment");
        }

 
        data.balance -= requiredPayment;
    } catch(std::bad_cast& err) {
        throw PaymentDeclinedError("We don't have crypto data-type to process payment");
    }
}
