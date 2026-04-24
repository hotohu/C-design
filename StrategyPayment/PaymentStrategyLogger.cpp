#include <iostream>

#include "PaymentStrategyLogger.h"
#include "PaymentError.h"

struct RequestLogger {
    RequestLogger(const PaymentRequest& iRequest) {
        _request = iRequest;
        std::cerr << "Starting the payment - " << PaymentTypeToString(_request.type) << std::endl;  
    }

    ~RequestLogger() {
        std::cerr << "Payment completed - " << PaymentTypeToString(_request.type) << std::endl;
    }

    PaymentRequest _request;
};

PaymentStrategyLogger::PaymentStrategyLogger(PaymentStrategyPtr iStrategy) 
: _strategy(std::move(iStrategy))
{
}

void PaymentStrategyLogger::MakePayment(const PaymentRequest& iRequest, PaymentContext& iData) const
{
    RequestLogger logger(iRequest);
    try {
        _strategy->MakePayment(iRequest, iData);
    } catch (const PaymentError& err) {
        std::cerr << err.what() << std::endl;
        throw PaymentError("Payment wasn't process right");
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        throw;
    }

    std::cerr << "Payment secceed" << std::endl;
}
