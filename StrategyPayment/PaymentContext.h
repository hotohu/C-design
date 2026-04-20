#pragma once

struct PaymentContext 
{    
    virtual ~PaymentContext() = default;
};

struct CreditCardPaymentData final : PaymentContext 
{
    double limit = 0;
};

struct CryptoPaymentData final : PaymentContext 
{
    bool walletValidated = false;
    double balance = 0;
    double feeInPercent = 0;
};