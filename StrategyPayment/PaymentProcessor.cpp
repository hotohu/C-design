#include "PaymentProcessor.h"
#include "PaymentError.h"

void PaymentProcessor::process(const PaymentRequest& iRequest, PaymentContext& iData)
{
    if (!_strategies.count(iRequest.type)) {
        throw PaymentResolvingError("We can't process request: this strategy wasn't supported - " + std::string(PaymentTypeToString(iRequest.type)));
    }

    _strategies[iRequest.type]->MakePayment(iRequest, iData);
}

void PaymentProcessor::processDefault(const PaymentRequest& iRequest, PaymentContext& iData)
{
    if (!_defaultType) {
        throw PaymentResolvingError("We can't process default payment: default type wasn't supported");
    }

    PaymentRequest request = iRequest;
    request.type = _defaultType.value();

    process(request, iData);
}

void PaymentProcessor::registerStrategy(PaymentType iType, PaymentStrategyPtr&& iStrategy) noexcept
{
    PaymentStrategyPtr loggerWrapper = std::make_unique<PaymentStrategyLogger>(std::move(iStrategy));
    _strategies[iType] = std::move(loggerWrapper);
}

void PaymentProcessor::registerDefaultStrategy(PaymentType iType, PaymentStrategyPtr&& iStrategy) noexcept
{
    registerStrategy(iType, std::move(iStrategy));
    _defaultType.emplace(iType);
}

void PaymentProcessor::unregisterStrategy(PaymentType iType)
{
    if (!_strategies.count(iType)) {
        throw PaymentResolvingError("We can't unregister strategy: this strategy has not been registered - " + std::string(PaymentTypeToString(iType)));
    }

    if (_defaultType && iType == _defaultType.value()) {
        _defaultType.reset();
    }

    _strategies.erase(iType);
}
