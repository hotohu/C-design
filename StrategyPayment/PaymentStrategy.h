#pragma once

#include <string>
#include <memory>

class PaymentStrategy;
using PaymentStrategyPtr = std::unique_ptr<PaymentStrategy>;

enum class PaymentType
{
    CreditCard,
    PayPal,
    Crypto,
    BankTransfer
};

struct PaymentRequest
{
    PaymentType type;
    double amount;
    std::string currency;
};

enum class PaymentResult
{
    OK,
    FAIL,
};

class PaymentStrategy 
{
public:
    virtual PaymentResult MakePayment(const PaymentRequest& request) = 0;
    virtual ~PaymentStrategy() {};
};

class MockBankService;

class CreditCardStrategy : public PaymentStrategy
{
public:
    CreditCardStrategy();
    PaymentResult MakePayment(const PaymentRequest& request) override;
    
private:
    using BankServicePtr = std::unique_ptr<MockBankService>;
    BankServicePtr _service;
};

class MockBankService
{
public:
    MockBankService() {};

    MockBankService(const MockBankService&) = delete;
    MockBankService operator=(const MockBankService&) = delete;

    MockBankService(const MockBankService&&) = delete;
    MockBankService operator=(const MockBankService&&) = delete;

    double GetLimit() const { return _limit; }
    std::string GetCurrency() const { return _currency; };

    void ProcessTransaction(double amount);

    virtual ~MockBankService() {}

private:
    double _limit = 1000;
    std::string _currency = "USD";
};

/*
class CryptoStrategy : public PaymentStrategy
{
public:
    CryptoStrategy() {};

private:
    virtual PaymentResult MakePaymentImpl(const PaymentRequest& request);

    using MockCryptoServicePtr = std::unique_ptr<MockCryptoService>;
    MockCryptoServicePtr _cryptoService;
};

class MockCryptoService
{
public:
    MockCryptoService() {}

    MockCryptoService(const MockCryptoService&) = delete;
    MockCryptoService operator=(const MockCryptoService&) = delete;

    MockCryptoService(const MockCryptoService&&) = delete;
    MockCryptoService operator=(const MockCryptoService&&) = delete;

    double GetBalance() const { return _balance; };
    double GetCurrentFee() const { return _currentFee; };
    bool VerifyWallet() const;

    std::string GetCurrency() const { return _currency; };
    void ProcessTransaction(double amount);

    virtual ~MockCryptoService() {};

private:
    double _balance = 100000;
    double _currentFee = 12500;
    std::string _currency = "BTC";
};

*/

