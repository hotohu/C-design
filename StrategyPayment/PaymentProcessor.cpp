#include "PaymentProcessor.h"

void PaymentProcessor::process(const PaymentRequest& iRequest, PaymentData& iData)
{
    if (!_strategies.count(iRequest.type)) {
        throw StrategyError("This strategy wasn't supported - " + std::string(PaymentTypeToString(iRequest.type)));
    }

    PaymentStrategyPtr loggerWrapper = std::make_unique<PaymentStrategyLogger>(std::move(_strategies[iRequest.type]));

    loggerWrapper->MakePayment(iRequest, iData);
}

void PaymentProcessor::processDefault(const PaymentRequest& iRequest, PaymentData& iData)
{
    PaymentRequest request = iRequest;

    // can be exception
    request.type = _defaultType.value();

    process(request, iData);
}

void PaymentProcessor::registerStrategy(PaymentType iType, PaymentStrategyPtr&& iStrategy)
{
    _strategies[iType] = std::move(iStrategy);
}

void PaymentProcessor::registerDefaultStrategy(PaymentType iType, PaymentStrategyPtr&& iStrategy)
{
    registerStrategy(iType, std::move(iStrategy));
    _defaultType.emplace(iType);
}

void PaymentProcessor::unregisterStrategy(PaymentType iType)
{
    _strategies.erase(iType);
}
