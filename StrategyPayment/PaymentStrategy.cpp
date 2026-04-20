#include "PaymentStrategy.h"

const char* PaymentTypeToString(PaymentType type) {
    switch (type) {
        case PaymentType::CreditCard: return "CreditCard";
        case PaymentType::Crypto: return "Crypto";
        case PaymentType::Alipay: return "Alipay";
        default: return "Unknown";
    }
}

void CreditCardStrategy::MakePayment(const PaymentRequest& request, PaymentData& iData) const
{
    CreditCardPaymentData& data = dynamic_cast<CreditCardPaymentData&>(iData);
    if (request.amount > data.limit) {
        throw BalanceExceededError("Limit of the credit card less than amount");
    }

    data.limit -= request.amount;
}


void CryptoStrategy::MakePayment(const PaymentRequest& request, PaymentData& iData) const
{
    CryptoPaymentData& data = dynamic_cast<CryptoPaymentData&>(iData);
    if (request.amount > data.feeInPercent + data.balance) {
        throw BalanceExceededError("Balance of the wallet less than amount and fee");
    }

    double requiredPayment = data.feeInPercent + request.amount;
    data.balance -= requiredPayment;
}
