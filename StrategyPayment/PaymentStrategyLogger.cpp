#include <iostream>

#include "PaymentStrategyLogger.h"
#include "PaymentError.h"
#include "PaymentLogger.h"

PaymentStrategyLogger::PaymentStrategyLogger(PaymentStrategyPtr iStrategy) 
: _strategy(std::move(iStrategy))
{
}

void PaymentStrategyLogger::Process(const PaymentRequest& iRequest, PaymentContext& iData) const
{
    PaymentLogger logger("Starting the payment - " + std::string(PaymentTypeToString(iRequest.type)), 
                        "Payment completed - " + std::string(PaymentTypeToString(iRequest.type)));
    try {
        _strategy->Process(iRequest, iData);
    } catch (const PaymentError& err) {
        std::cerr << err.what() << std::endl;
        throw PaymentError("Payment wasn't process right");
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        throw;
    }

    std::cerr << "Payment secceed" << std::endl;
}
