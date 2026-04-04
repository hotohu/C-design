#pragma once

#include "PaymentStrategy.h"

class PaymentStrategyLogger : public PaymentStrategy
{
public:
    PaymentStrategyLogger(PaymentStrategyPtr iStrategy) : _strategy(std::move(iStrategy))
    {}

    PaymentResult MakePayment(const PaymentRequest& request) override;
    virtual ~PaymentStrategyLogger() {};

private:
    PaymentStrategyPtr _strategy;
};