#include <iostream>

#include "PaymentStrategyLogger.h"

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

void PaymentStrategyLogger::MakePayment(const PaymentRequest& iRequest) 
{
    RequestLogger logger(iRequest);
    _strategy->MakePayment(iRequest);
}
