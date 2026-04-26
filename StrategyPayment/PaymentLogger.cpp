#include "PaymentLogger.h"

PaymentLogger::PaymentLogger(std::string&& iStart, std::string&& iEnd) 
: _start(iStart), _end(iEnd) {
    std::cerr << _start << std::endl;
}

PaymentLogger::~PaymentLogger() {
    std::cerr << _end << std::endl;
}
