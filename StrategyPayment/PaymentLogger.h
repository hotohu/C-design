
#pragma once

#include <string>
#include <iostream>

struct PaymentLogger {
    PaymentLogger(std::string&& iStart, std::string&& iEnd);
    ~PaymentLogger();

    std::string _start;
    std::string _end;
};
