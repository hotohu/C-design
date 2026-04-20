#pragma once

#include <stdexcept>

class PaymentError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class PaymentResolvingError : public PaymentError {
public:
    using PaymentError::PaymentError;
};

class PaymentDeclinedError : public PaymentError {
public:
    using PaymentError::PaymentError;
};
