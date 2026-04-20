#pragma once

#include <functional>
#include <unordered_map>
#include <optional>

#include "PaymentStrategyLogger.h"

class PaymentProcessor final
{
public:
    void process(const PaymentRequest& iRequest, PaymentContext& oData);
    void processDefault(const PaymentRequest& iRequest, PaymentContext& oData);

    virtual ~PaymentProcessor() = default;


    void registerStrategy(PaymentType iType, PaymentStrategyPtr&& iStrategy) noexcept;
    void registerDefaultStrategy(PaymentType iType, PaymentStrategyPtr&& iStrategy) noexcept;
    
    void unregisterStrategy(PaymentType iType);

private:
    std::unordered_map<PaymentType, PaymentStrategyPtr> _strategies;
    std::optional<PaymentType> _defaultType;
};