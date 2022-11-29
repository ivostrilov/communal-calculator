#include "core/model_test.h"

#include "core/app_cfg_manager_test.h"
#include "core/app_configuration.h"
#include "core/workspace_test.h"
#include "wrappers/std_filesystem_wrapper_test.h"

namespace CommunalCalculator::Core::Test {

TEST_F(ModelTest, CalculateSummaryPassingArgs) {
  Calculator::CommunalCounters communal_counters = {
      {CommunalCounter::Type::kColdWater, {}},
      {CommunalCounter::Type::kElectricityT1, {}}};

  EXPECT_CALL(*modelMock_, Calculate(::testing::_, communal_counters));

  auto communal_counters_copy = communal_counters;
  modelMock_->RealCalculateSummary(std::move(communal_counters_copy));
}

TEST_F(ModelTest, InitializeSuccessfulFlow) {
  EXPECT_CALL(*modelMock_, InitializeConfig);
  modelMock_->RealInitialize();
}

TEST_F(ModelTest, InitializeConfigSuccessfulReading) {
  constexpr std::string_view kUserHomePath = "/home/user/";
  constexpr std::string_view kConfigPath = ".config/CommunalCalculator";
  constexpr float kExpectedHotWaterTariff = 54.89;

  WorkspaceMock workspace_mock;
  EXPECT_CALL(workspace_mock, GetUserHomePath)
      .WillOnce(::testing::Return(kUserHomePath));

  Wrappers::Test::STDFilesystemWrapperMock filesystem_wrapper_mock;

  std::filesystem::path expected_config_path = kUserHomePath;
  expected_config_path /= kConfigPath;

  EXPECT_CALL(filesystem_wrapper_mock,
              Exists(::testing::Eq(expected_config_path)))
      .WillOnce(::testing::Return(false));

  EXPECT_CALL(
      filesystem_wrapper_mock,
      CreateDirectories(::testing::Eq(expected_config_path), ::testing::_))
      .WillOnce(::testing::Return(true));

  AppCfgManagerMock app_cfg_manager_mock;

  EXPECT_CALL(app_cfg_manager_mock,
              SetDirPath(::testing::Eq(expected_config_path)));

  auto app_configuration_ptr = std::make_shared<AppConfiguration>();
  app_configuration_ptr->SetHotWaterTariff(kExpectedHotWaterTariff);

  EXPECT_CALL(app_cfg_manager_mock, GetCfg())
      .WillOnce(::testing::Return(app_configuration_ptr));

  bool connection_called = false;
  AppConfiguration pulled_app_configuration;

  auto connection = [&connection_called, &pulled_app_configuration, this]() {
    connection_called = true;
    pulled_app_configuration = modelMock_->appConfigurationObserver_.PullCopy();
  };

  modelMock_->appConfigurationObserver_.SetConnection(connection);
  modelMock_->RealInitializeConfig(app_cfg_manager_mock, workspace_mock,
                                   filesystem_wrapper_mock);

  ASSERT_TRUE(connection_called);
  EXPECT_EQ(app_configuration_ptr->GetHotWaterTariff(),
            pulled_app_configuration.GetHotWaterTariff());
}

TEST_F(ModelTest, InitializeConfigCfgManagerReturnedEmptyPtr) {
  constexpr float kExpectedHotWaterTariff = 54.89;

  WorkspaceMock workspace_mock;
  EXPECT_CALL(workspace_mock, GetUserHomePath);

  Wrappers::Test::STDFilesystemWrapperMock filesystem_wrapper_mock;
  EXPECT_CALL(filesystem_wrapper_mock, Exists)
      .WillOnce(::testing::Return(false));
  EXPECT_CALL(filesystem_wrapper_mock, CreateDirectories)
      .WillOnce(::testing::Return(true));

  AppCfgManagerMock app_cfg_manager_mock;
  EXPECT_CALL(app_cfg_manager_mock, SetDirPath);

  EXPECT_CALL(app_cfg_manager_mock, GetCfg)
      .WillOnce(::testing::Return(std::shared_ptr<AppConfiguration>()));

  auto generated_cfg = std::make_shared<AppConfiguration>();
  generated_cfg->SetHotWaterTariff(kExpectedHotWaterTariff);

  EXPECT_CALL(app_cfg_manager_mock, GenerateConfig)
      .WillOnce(::testing::Return(generated_cfg));

  EXPECT_CALL(app_cfg_manager_mock, SaveCfg(::testing::Eq(generated_cfg)));

  bool connection_called = false;
  AppConfiguration pulled_app_configuration;

  auto connection = [&connection_called, &pulled_app_configuration, this]() {
    connection_called = true;
    pulled_app_configuration = modelMock_->appConfigurationObserver_.PullCopy();
  };

  modelMock_->appConfigurationObserver_.SetConnection(connection);
  modelMock_->RealInitializeConfig(app_cfg_manager_mock, workspace_mock,
                                   filesystem_wrapper_mock);

  ASSERT_TRUE(connection_called);
  EXPECT_EQ(generated_cfg->GetHotWaterTariff(),
            pulled_app_configuration.GetHotWaterTariff());
}

TEST_F(ModelTest, CalculatePassingArgs) {
  constexpr float kWaterSinkTariff = 2;

  auto hot_water = CalculatorTest::CreateCommunalCounterMock();
  auto cold_water = CalculatorTest::CreateCommunalCounterMock();

  Calculator::CommunalCounters communal_counters = {
      {CommunalCounter::Type::kColdWater, cold_water},
      {CommunalCounter::Type::kHotWater, hot_water}};

  EXPECT_CALL(calculatorMock_, SetCounter(::testing::Eq(cold_water)));
  EXPECT_CALL(calculatorMock_, SetCounter(::testing::Eq(hot_water)));
  EXPECT_CALL(calculatorMock_, SetWaterSinkTariff(kWaterSinkTariff));
  EXPECT_CALL(calculatorMock_, CalculateSummary);

  auto app_cfg = modelMock_->appConfigurationObserver_.PullCopy();
  app_cfg.SetWaterSinkTariff(kWaterSinkTariff);
  modelMock_->appConfigurationObserver_.Push(app_cfg);

  modelMock_->RealCalculate(calculatorMock_, communal_counters);
}

TEST_F(ModelTest, CalculateNotifyObserver) {
  constexpr float kResult = 100;
  constexpr char const *kCalculationLog = "(calculation log)";

  Calculator::CommunalCounters communal_counters = {
      {CommunalCounter::Type::kColdWater, {}},
      {CommunalCounter::Type::kHotWater, {}}};

  EXPECT_CALL(calculatorMock_, SetCounter).Times(2);
  EXPECT_CALL(calculatorMock_, SetWaterSinkTariff);

  auto calculate_summary = [](std::string *out_log) -> float {
    assert(out_log != nullptr);
    *out_log = "(calculation log)";
    return kResult;
  };

  EXPECT_CALL(calculatorMock_, CalculateSummary)
      .WillOnce(::testing::Invoke(calculate_summary));

  bool connection_called = false;
  Model::Calculation calculation;

  auto connection = [&connection_called, &calculation, this]() {
    connection_called = true;
    calculation = modelMock_->calculationResultObserver_.PullCopy();
  };

  modelMock_->calculationResultObserver_.SetConnection(std::move(connection));
  modelMock_->RealCalculate(calculatorMock_, communal_counters);

  ASSERT_TRUE(connection_called);
  EXPECT_EQ(kResult, calculation.result);
  EXPECT_EQ(kCalculationLog, calculation.log);
}

}  // namespace CommunalCalculator::Core::Test
