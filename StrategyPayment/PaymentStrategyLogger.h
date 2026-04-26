#pragma once

#include "PaymentStrategy.h"

class PaymentStrategyLogger : public PaymentStrategy
{
public:
    explicit PaymentStrategyLogger(PaymentStrategyPtr iStrategy);

    void Process(const PaymentRequest& request, PaymentContext& iData) const override;
    virtual ~PaymentStrategyLogger() = default;

private:
    PaymentStrategyPtr _strategy;
    std::string _requestType = "";
};