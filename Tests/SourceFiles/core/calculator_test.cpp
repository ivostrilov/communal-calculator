#include "core/calculator_test.h"

namespace CommunalCalculator::Core::Test {

TEST_F(CalculatorTest, CalculateSummaryColdHotWaterCalculation) {
  constexpr char const *kColdWaterName = "Cold Water";
  constexpr int kColdWaterPrevValue = 100;
  constexpr int kColdWaterCurValue = 200;
  constexpr int kColdWaterTariffValue = 10;

  constexpr int kColdWaterSummary =
      (kColdWaterCurValue - kColdWaterPrevValue) * kColdWaterTariffValue;

  constexpr char const *kColdWaterPrevStr = "100";
  constexpr char const *kColdWaterCurStr = "200";
  constexpr char const *kColdWaterTariffStr = "10";
  constexpr char const *kColdWaterSummaryStr = "1000";

  constexpr char const *kHotWaterName = "Hot Water";
  constexpr int kHotWaterPrevValue = 2000;
  constexpr int kHotWaterCurValue = 4000;
  constexpr int kHotWaterTariffValue = 5;

  constexpr int kHotWaterSummary =
      (kHotWaterCurValue - kHotWaterPrevValue) * kHotWaterTariffValue;

  constexpr char const *kHotWaterPrevStr = "2000";
  constexpr char const *kHotWaterCurStr = "4000";
  constexpr char const *kHotWaterTariffStr = "5";
  constexpr char const *kHotWaterSummaryStr = "10000";

  constexpr float kWaterSinkSummary = 50;

  constexpr int kExpectedResult = 11050;
  constexpr char const *kExpectedCalculationLog =
      "Cold Water: |200 - 100| * 10 = 1000\n"
      "Hot Water: |4000 - 2000| * 5 = 10000\n"
      "(water_sink_calculation)";

  auto cold_water = CreateCommunalCounterMock();
  EXPECT_CALL(*cold_water, GetName).WillOnce(::testing::Return(kColdWaterName));
  EXPECT_CALL(*cold_water, GetType)
      .WillRepeatedly(::testing::Return(CommunalCounter::Type::kColdWater));
  EXPECT_CALL(*cold_water, GetPrevValue)
      .WillOnce(::testing::Return(kColdWaterPrevValue));
  EXPECT_CALL(*cold_water, GetCurValue)
      .WillOnce(::testing::Return(kColdWaterCurValue));
  EXPECT_CALL(*cold_water, GetTariffValue)
      .WillOnce(::testing::Return(kColdWaterTariffValue));

  auto hot_water = CreateCommunalCounterMock();
  EXPECT_CALL(*hot_water, GetName).WillOnce(::testing::Return(kHotWaterName));
  EXPECT_CALL(*hot_water, GetType)
      .WillRepeatedly(::testing::Return(CommunalCounter::Type::kHotWater));
  EXPECT_CALL(*hot_water, GetPrevValue)
      .WillOnce(::testing::Return(kHotWaterPrevValue));
  EXPECT_CALL(*hot_water, GetCurValue)
      .WillOnce(::testing::Return(kHotWaterCurValue));
  EXPECT_CALL(*hot_water, GetTariffValue)
      .WillOnce(::testing::Return(kHotWaterTariffValue));

  const Calculator::CommunalCounters communal_counters = {
      {CommunalCounter::Type::kColdWater, cold_water},
      {CommunalCounter::Type::kHotWater, hot_water}};

  EXPECT_CALL(*calculatorMock_, GetCounters)
      .WillOnce(::testing::ReturnRef(communal_counters));

  EXPECT_CALL(*calculatorMock_, ToString(kColdWaterPrevValue))
      .WillOnce(::testing::Return(kColdWaterPrevStr));
  EXPECT_CALL(*calculatorMock_, ToString(kColdWaterCurValue))
      .WillOnce(::testing::Return(kColdWaterCurStr));
  EXPECT_CALL(*calculatorMock_, ToString(kColdWaterTariffValue))
      .WillOnce(::testing::Return(kColdWaterTariffStr));
  EXPECT_CALL(*calculatorMock_, ToString(kColdWaterSummary))
      .WillOnce(::testing::Return(kColdWaterSummaryStr));

  EXPECT_CALL(*calculatorMock_, ToString(kHotWaterPrevValue))
      .WillOnce(::testing::Return(kHotWaterPrevStr));
  EXPECT_CALL(*calculatorMock_, ToString(kHotWaterCurValue))
      .WillOnce(::testing::Return(kHotWaterCurStr));
  EXPECT_CALL(*calculatorMock_, ToString(kHotWaterTariffValue))
      .WillOnce(::testing::Return(kHotWaterTariffStr));
  EXPECT_CALL(*calculatorMock_, ToString(kHotWaterSummary))
      .WillOnce(::testing::Return(kHotWaterSummaryStr));

  auto calculate_water_sink_summary = [](std::string *calculation_log) {
    assert(calculation_log);
    *calculation_log = "(water_sink_calculation)";
    return kWaterSinkSummary;
  };

  EXPECT_CALL(*calculatorMock_, CalculateWaterSinkSummary)
      .WillOnce(::testing::Invoke(calculate_water_sink_summary));

  std::string calculation_log;
  auto actually = calculatorMock_->RealCalculateSummary(&calculation_log);

  EXPECT_EQ(kExpectedResult, actually);
  EXPECT_EQ(kExpectedCalculationLog, calculation_log);
}

TEST_F(CalculatorTest, CalculateWaterSinkSummaryColdWater) {
  constexpr int kColdWaterPrevValue = 100;
  constexpr int kColdWaterCurValue = 200;
  constexpr char const *kColdWaterPrevStr = "100";
  constexpr char const *kColdWaterCurStr = "200";

  constexpr float kWaterSinkTariff = 3;
  constexpr char const *kWaterSinkTariffStr = "3";

  constexpr float kExpectedResult = 300;
  constexpr char const *kExpectedResultStr = "300";
  constexpr char const *kExpectedCalculationLog =
      "Water Sink: |200 - 100| * 3 = 300";

  auto cold_water = CreateCommunalCounterMock();
  EXPECT_CALL(*cold_water, GetType)
      .WillRepeatedly(::testing::Return(CommunalCounter::Type::kColdWater));
  EXPECT_CALL(*cold_water, GetPrevValue)
      .WillOnce(::testing::Return(kColdWaterPrevValue));
  EXPECT_CALL(*cold_water, GetCurValue)
      .WillOnce(::testing::Return(kColdWaterCurValue));

  const Calculator::CommunalCounters communal_counters = {
      {CommunalCounter::Type::kColdWater, cold_water}};

  EXPECT_CALL(*calculatorMock_, GetCounters)
      .WillOnce(::testing::ReturnRef(communal_counters));
  EXPECT_CALL(*calculatorMock_, GetWaterSinkTariff)
      .WillOnce(::testing::Return(kWaterSinkTariff));

  EXPECT_CALL(*calculatorMock_, ToString(kColdWaterPrevValue))
      .WillOnce(::testing::Return(kColdWaterPrevStr));
  EXPECT_CALL(*calculatorMock_, ToString(kColdWaterCurValue))
      .WillOnce(::testing::Return(kColdWaterCurStr));
  EXPECT_CALL(*calculatorMock_, ToString(kWaterSinkTariff))
      .WillOnce(::testing::Return(kWaterSinkTariffStr));
  EXPECT_CALL(*calculatorMock_, ToString(kExpectedResult))
      .WillOnce(::testing::Return(kExpectedResultStr));

  std::string calculation_log;
  auto actually =
      calculatorMock_->RealCalculateWaterSinkSummary(&calculation_log);

  EXPECT_EQ(kExpectedResult, actually);
  EXPECT_EQ(kExpectedCalculationLog, calculation_log);
}

TEST_F(CalculatorTest, CalculateWaterSinkSummaryHotWater) {
  constexpr int kHotWaterPrevValue = 2000;
  constexpr int kHotWaterCurValue = 4000;
  constexpr char const *kHotWaterPrevStr = "2000";
  constexpr char const *kHotWaterCurStr = "4000";

  constexpr float kWaterSinkTariff = 3;
  constexpr char const *kWaterSinkTariffStr = "3";

  constexpr float kExpectedResult = 6000;
  constexpr char const *kExpectedResultStr = "6000";
  constexpr char const *kExpectedCalculationLog =
      "Water Sink: |4000 - 2000| * 3 = 6000";

  auto hot_water = CreateCommunalCounterMock();
  EXPECT_CALL(*hot_water, GetType)
      .WillRepeatedly(::testing::Return(CommunalCounter::Type::kHotWater));
  EXPECT_CALL(*hot_water, GetPrevValue)
      .WillOnce(::testing::Return(kHotWaterPrevValue));
  EXPECT_CALL(*hot_water, GetCurValue)
      .WillOnce(::testing::Return(kHotWaterCurValue));

  const Calculator::CommunalCounters communal_counters = {
      {CommunalCounter::Type::kHotWater, hot_water}};

  EXPECT_CALL(*calculatorMock_, GetCounters)
      .WillOnce(::testing::ReturnRef(communal_counters));
  EXPECT_CALL(*calculatorMock_, GetWaterSinkTariff)
      .WillOnce(::testing::Return(kWaterSinkTariff));

  EXPECT_CALL(*calculatorMock_, ToString(kHotWaterPrevValue))
      .WillOnce(::testing::Return(kHotWaterPrevStr));
  EXPECT_CALL(*calculatorMock_, ToString(kHotWaterCurValue))
      .WillOnce(::testing::Return(kHotWaterCurStr));
  EXPECT_CALL(*calculatorMock_, ToString(kWaterSinkTariff))
      .WillOnce(::testing::Return(kWaterSinkTariffStr));
  EXPECT_CALL(*calculatorMock_, ToString(kExpectedResult))
      .WillOnce(::testing::Return(kExpectedResultStr));

  std::string calculation_log;
  auto actually =
      calculatorMock_->RealCalculateWaterSinkSummary(&calculation_log);

  EXPECT_EQ(kExpectedResult, actually);
  EXPECT_EQ(kExpectedCalculationLog, calculation_log);
}

TEST_F(CalculatorTest, CalculateWaterSinkSummaryColdHotWater) {
  constexpr int kColdWaterPrevValue = 100;
  constexpr int kColdWaterCurValue = 200;
  constexpr char const *kColdWaterPrevStr = "100";
  constexpr char const *kColdWaterCurStr = "200";

  constexpr int kHotWaterPrevValue = 2000;
  constexpr int kHotWaterCurValue = 4000;
  constexpr char const *kHotWaterPrevStr = "2000";
  constexpr char const *kHotWaterCurStr = "4000";

  constexpr float kWaterSinkTariff = 3;
  constexpr char const *kWaterSinkTariffStr = "3";

  constexpr float kExpectedResult = 6300;
  constexpr char const *kExpectedResultStr = "6300";
  constexpr char const *kExpectedCalculationLog =
      "Water Sink: |200 - 100| * 3 + |4000 - 2000| * 3 = 6300";

  auto cold_water = CreateCommunalCounterMock();
  EXPECT_CALL(*cold_water, GetType)
      .WillRepeatedly(::testing::Return(CommunalCounter::Type::kColdWater));
  EXPECT_CALL(*cold_water, GetPrevValue)
      .WillOnce(::testing::Return(kColdWaterPrevValue));
  EXPECT_CALL(*cold_water, GetCurValue)
      .WillOnce(::testing::Return(kColdWaterCurValue));

  auto hot_water = CreateCommunalCounterMock();
  EXPECT_CALL(*hot_water, GetType)
      .WillRepeatedly(::testing::Return(CommunalCounter::Type::kHotWater));
  EXPECT_CALL(*hot_water, GetPrevValue)
      .WillOnce(::testing::Return(kHotWaterPrevValue));
  EXPECT_CALL(*hot_water, GetCurValue)
      .WillOnce(::testing::Return(kHotWaterCurValue));

  const Calculator::CommunalCounters communal_counters = {
      {CommunalCounter::Type::kColdWater, cold_water},
      {CommunalCounter::Type::kHotWater, hot_water}};

  EXPECT_CALL(*calculatorMock_, GetCounters)
      .WillOnce(::testing::ReturnRef(communal_counters));
  EXPECT_CALL(*calculatorMock_, GetWaterSinkTariff)
      .WillOnce(::testing::Return(kWaterSinkTariff));

  EXPECT_CALL(*calculatorMock_, ToString(kColdWaterPrevValue))
      .WillOnce(::testing::Return(kColdWaterPrevStr));
  EXPECT_CALL(*calculatorMock_, ToString(kColdWaterCurValue))
      .WillOnce(::testing::Return(kColdWaterCurStr));

  EXPECT_CALL(*calculatorMock_, ToString(kHotWaterPrevValue))
      .WillOnce(::testing::Return(kHotWaterPrevStr));
  EXPECT_CALL(*calculatorMock_, ToString(kHotWaterCurValue))
      .WillOnce(::testing::Return(kHotWaterCurStr));

  EXPECT_CALL(*calculatorMock_, ToString(kWaterSinkTariff))
      .WillRepeatedly(::testing::Return(kWaterSinkTariffStr));
  EXPECT_CALL(*calculatorMock_, ToString(kExpectedResult))
      .WillOnce(::testing::Return(kExpectedResultStr));

  std::string calculation_log;
  auto actually =
      calculatorMock_->RealCalculateWaterSinkSummary(&calculation_log);

  EXPECT_EQ(kExpectedResult, actually);
  EXPECT_EQ(kExpectedCalculationLog, calculation_log);
}

TEST_F(CalculatorTest, ToString15) {
  constexpr float kInput = 15;
  constexpr char const *kExpected = "15.00";

  auto actually = calculatorMock_->RealToString(kInput);
  EXPECT_EQ(kExpected, actually);
}

TEST_F(CalculatorTest, ToString15D1998) {
  constexpr float kInput = 15.1998;
  constexpr char const *kExpected = "15.20";

  auto actually = calculatorMock_->RealToString(kInput);
  EXPECT_EQ(kExpected, actually);
}

TEST_F(CalculatorTest, ToString15D268) {
  constexpr float kInput = 15.268;
  constexpr char const *kExpected = "15.27";

  auto actually = calculatorMock_->RealToString(kInput);
  EXPECT_EQ(kExpected, actually);
}

TEST_F(CalculatorTest, ToString15D265) {
  constexpr float kInput = 15.265;
  constexpr char const *kExpected = "15.27";

  auto actually = calculatorMock_->RealToString(kInput);
  EXPECT_EQ(kExpected, actually);
}

TEST_F(CalculatorTest, ToString15D262) {
  constexpr float kInput = 15.262;
  constexpr char const *kExpected = "15.26";

  auto actually = calculatorMock_->RealToString(kInput);
  EXPECT_EQ(kExpected, actually);
}

}  // namespace CommunalCalculator::Core::Test
