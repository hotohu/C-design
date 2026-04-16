#pragma once

#include <functional>
#include <unordered_map>
#include <optional>

#include "PaymentStrategyLogger.h"

class StrategyError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class PaymentProcessor final
{
public:
    void process(const PaymentRequest& iRequest);
    void processDefault(const PaymentRequest& iRequest);

    virtual ~PaymentProcessor() = default;


    void registerStrategy(PaymentType iType, PaymentStrategyPtr&& iStrategy);
    void registerDefaultStrategy(PaymentType iType, PaymentStrategyPtr&& iStrategy);
    
    void unregisterStrategy(PaymentType iType);

private:
    std::unordered_map<PaymentType, PaymentStrategyPtr> _strategies;
    std::optional<PaymentType> _defaultType;
};