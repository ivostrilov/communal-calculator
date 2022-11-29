#ifndef TESTS_SOURCEFILES_CORE_CALCULATOR_TEST_H_
#define TESTS_SOURCEFILES_CORE_CALCULATOR_TEST_H_

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "core/calculator.h"
#include "core/communal_counter_test.h"

namespace CommunalCalculator::Core::Test {

class CalculatorMock;

class CalculatorTest : public ::testing::Test {
 public:
  static auto CreateCommunalCounterMock()
      -> std::shared_ptr<CommunalCounterMock> {
    return std::make_shared<CommunalCounterMock>();
  }

  void SetUp() override {
    calculatorMock_ = std::make_unique<CalculatorMock>();
  }

  std::unique_ptr<CalculatorMock> calculatorMock_;
};

class CalculatorMock : public Calculator {
 public:
  MOCK_METHOD(void, SetWaterSinkTariff, (float value), (override));
  MOCK_METHOD(float, GetWaterSinkTariff, (), (const override));

  MOCK_METHOD(void, SetCounter,
              (const std::shared_ptr<CommunalCounter> &counter), (override));
  MOCK_METHOD(const CommunalCounters &, GetCounters, (), (const override));

  MOCK_METHOD(float, CalculateSummary, (std::string * calculation_log),
              (override));
  auto RealCalculateSummary(std::string *calculation_log) -> float {
    return Calculator::CalculateSummary(calculation_log);
  }

  MOCK_METHOD(float, CalculateWaterSinkSummary, (std::string * calculation_log),
              (override));
  auto RealCalculateWaterSinkSummary(std::string *calculation_log) -> float {
    return Calculator::CalculateWaterSinkSummary(calculation_log);
  }

  MOCK_METHOD(std::string, ToString, (float number), (override));
  auto RealToString(float number) -> std::string {
    return Calculator::ToString(number);
  }
};

}  // namespace CommunalCalculator::Core::Test

#endif  // TESTS_SOURCEFILES_CORE_CALCULATOR_TEST_H_
