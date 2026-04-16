#pragma once

#include "PaymentStrategy.h"

class PaymentStrategyLogger : public PaymentStrategy
{
public:
    explicit PaymentStrategyLogger(PaymentStrategyPtr iStrategy);

    void MakePayment(const PaymentRequest& iRequest) override;
    virtual ~PaymentStrategyLogger() = default;

private:
    PaymentStrategyPtr _strategy;
    std::string _requestType = "";
};