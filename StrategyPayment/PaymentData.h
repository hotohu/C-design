#pragma once

struct PaymentData 
{    
    virtual ~PaymentData() = default;
};

struct CreditCardPaymentData final : PaymentData 
{
    using PaymentData::PaymentData;

    double limit = 0;
};

struct CryptoPaymentData final : PaymentData 
{
    using PaymentData::PaymentData;

    bool walletValidated = false;
    double balance = 0;
    double feeInPercent = 0;
};