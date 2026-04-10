#pragma once

#include "PaymentStrategyLogger.h"

class PaymentProcessor
{
public:
    explicit PaymentProcessor(PaymentStrategyPtr iStrategy);

    void process(const PaymentRequest& request) const;
    virtual ~PaymentProcessor() = default;

private:
    PaymentStrategyPtr _strategy;
};