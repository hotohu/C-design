#include "PaymentProcessor.h"
#include "PaymentError.h"

void PaymentProcessor::process(const PaymentRequest& iRequest, PaymentContext& iData)
{
    if (!_strategies.count(iRequest.type)) {
        throw PaymentResolvingError("We can't process request: this strategy wasn't supported - " + std::string(PaymentTypeToString(iRequest.type)));
    }

    _strategies[iRequest.type]->Process(iRequest, iData);
}

void PaymentProcessor::registerStrategy(PaymentType iType, PaymentStrategyPtr&& iStrategy) noexcept
{
    PaymentStrategyPtr loggerWrapper = std::make_unique<PaymentStrategyLogger>(std::move(iStrategy));
    _strategies[iType] = std::move(loggerWrapper);
}

void PaymentProcessor::unregisterStrategy(PaymentType iType)
{
    if (!_strategies.count(iType)) {
        throw PaymentResolvingError("We can't unregister strategy: this strategy has not been registered - " + std::string(PaymentTypeToString(iType)));
    }

    _strategies.erase(iType);
}
