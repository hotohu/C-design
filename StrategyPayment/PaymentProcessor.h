#pragma once

#include "PaymentStrategyLogger.h"

class PaymentProcessor
{
public:
    PaymentProcessor(PaymentStrategyPtr strategy) : _strategy(std::move(strategy)) {}

    PaymentResult process(const PaymentRequest& request);
    virtual ~PaymentProcessor() {};

private:
    PaymentStrategyPtr _strategy;
};