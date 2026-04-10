#pragma once

#include "PaymentStrategy.h"

class PaymentStrategyLogger : public PaymentStrategy
{
public:
    explicit PaymentStrategyLogger(PaymentStrategyPtr iStrategy);

    void MakePayment(const PaymentRequest& request) override;
    virtual ~PaymentStrategyLogger() = default;

private:
    PaymentStrategyPtr _strategy;
};