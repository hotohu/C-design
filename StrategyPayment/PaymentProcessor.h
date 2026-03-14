#pragma once

#include "PaymentStrategy.h"

class PaymentProcessor
{
public:
    PaymentResult process(const PaymentRequest& request);
    virtual ~PaymentProcessor() {};
};