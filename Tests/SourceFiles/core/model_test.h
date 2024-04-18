#ifndef TESTS_SOURCEFILES_CORE_MODEL_TEST_H_
#define TESTS_SOURCEFILES_CORE_MODEL_TEST_H_

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <utility>

#include "core/calculator_test.h"
#include "core/model.h"

namespace CommunalCalculator::Core::Test {

class ModelMock;

class ModelTest : public ::testing::Test {
 public:
  void SetUp() override { modelMock_ = std::make_unique<ModelMock>(); }

  std::unique_ptr<ModelMock> modelMock_;
  CalculatorMock calculatorMock_;
};

class ModelMock : public Core::Model {
 public:
  MOCK_METHOD(void, Initialize, (const std::filesystem::path &), (override));
  void RealInitialize(const std::filesystem::path &path) {
    Model::Initialize(path);
  }

  MOCK_METHOD(void, CalculateSummary,
              (Calculator::CommunalCounters && counters), (override));
  void RealCalculateSummary(Calculator::CommunalCounters &&counters) {
    Core::Model::CalculateSummary(std::move(counters));
  }

  MOCK_METHOD(void, InitializeConfig,
              (AppCfgManager & app_cfg_manager, Workspace &workspace,
               Wrappers::STDFilesystemWrapper &filesystem_wrapper),
              (override));
  void RealInitializeConfig(
      AppCfgManager &app_cfg_manager, Workspace &workspace,
      Wrappers::STDFilesystemWrapper &filesystem_wrapper) {
    Model::InitializeConfig(app_cfg_manager, workspace, filesystem_wrapper);
  }

  MOCK_METHOD(void, InitializeAppDataDir,
              (ValuesHistoryManager & values_history_manager,
               Wrappers::STDFilesystemWrapper &filesystem_wrapper,
               const std::filesystem::path &app_data_path),
              (override));

  MOCK_METHOD(void, Calculate,
              (Calculator & calculator,
               const Calculator::CommunalCounters &counters),
              (override));
  void RealCalculate(Calculator &calculator,
                     const Calculator::CommunalCounters &counters) {
    Core::Model::Calculate(calculator, counters);
  }
};

}  // namespace CommunalCalculator::Core::Test

#endif  // TESTS_SOURCEFILES_CORE_MODEL_TEST_H_
