#ifndef TESTS_SOURCEFILES_CORE_APP_CFG_MANAGER_TEST_H_
#define TESTS_SOURCEFILES_CORE_APP_CFG_MANAGER_TEST_H_

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "core/app_cfg_manager.h"
#include "wrappers/std_of_stream_wrapper_test.h"

namespace CommunalCalculator::Core::Test {

class AppCfgManagerMock;

class AppCfgManagerTest : public ::testing::Test {
 public:
  void SetUp() override {
    appCfgManagerMock_ = std::make_unique<AppCfgManagerMock>();
  }

  std::unique_ptr<AppCfgManagerMock> appCfgManagerMock_;
  Wrappers::Test::STDOfStreamWrapperMock stdOfStreamWrapperMock_;
};

class AppCfgManagerMock : public Core::AppCfgManager {
 public:
  MOCK_METHOD(void, SetDirPath, (const std::filesystem::path &dir_path),
              (override));
  MOCK_METHOD(const std::filesystem::path &, GetDirPath, (), (const override));

  MOCK_METHOD(std::shared_ptr<AppConfiguration>, GetCfg, (), (override));
  auto RealGetCfg() -> std::shared_ptr<AppConfiguration> {
    return AppCfgManager::GetCfg();
  }

  MOCK_METHOD(void, SaveCfg, (const std::shared_ptr<AppConfiguration> &cfg),
              (override));
  void RealSaveCfg(const std::shared_ptr<AppConfiguration> &cfg) {
    AppCfgManager::SaveCfg(cfg);
  }

  MOCK_METHOD(std::shared_ptr<AppConfiguration>, GenerateConfig, (),
              (override));
  auto RealGenerateConfig() -> std::shared_ptr<AppConfiguration> {
    return AppCfgManager::GenerateConfig();
  }

  MOCK_METHOD(std::string, CfgToString, (const AppConfiguration &), (override));
  auto RealCfgToString(const AppConfiguration &cfg) -> std::string {
    return AppCfgManager::CfgToString(cfg);
  }

  MOCK_METHOD(AppConfiguration, StringToCfg, (const std::string &), (override));
  auto RealStringToCfg(const std::string &str) -> AppConfiguration {
    return AppCfgManager::StringToCfg(str);
  }

  MOCK_METHOD(void, SaveFile,
              (Wrappers::STDOfStreamWrapper & of_stream, const char *data,
               size_t size),
              (override));
  void RealSaveFile(Wrappers::STDOfStreamWrapper &of_stream, const char *data,
                    size_t size) {
    AppCfgManager::SaveFile(of_stream, data, size);
  }
};

}  // namespace CommunalCalculator::Core::Test

#endif  // TESTS_SOURCEFILES_CORE_APP_CFG_MANAGER_TEST_H_
