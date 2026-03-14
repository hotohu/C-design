cmake_minimum_required(VERSION 3.12)
project(StrategyPayment)

set(SOURCES main.cpp
			PaymentProcessor.h
			PaymentProcessor.cpp
			PaymentStrategy.h
			PaymentStrategy.cpp)
			
add_executable(StrategyPayment ${SOURCES})

set_target_properties(
		StrategyPayment PROPERTIES
		CXX_STANDARD 20
		CXX_STANDARD_REQUIRED ON
)
