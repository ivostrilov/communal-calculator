#include "core/app_cfg_manager_test.h"

#include <stdexcept>

namespace CommunalCalculator::Core::Test {

TEST_F(AppCfgManagerTest, GetCfgSuccesfulFlow) {}

TEST_F(AppCfgManagerTest, SaveCfgSuccessfulFlow) {
  const std::string kCfgStr = "123";

  auto cfg = std::make_shared<AppConfiguration>();
  EXPECT_CALL(*appCfgManagerMock_, CfgToString(::testing::Ref(*cfg)))
      .WillOnce(::testing::Return(kCfgStr));

  EXPECT_CALL(
      *appCfgManagerMock_,
      SaveFile(::testing::_, ::testing::StrEq(kCfgStr), kCfgStr.size()));

  appCfgManagerMock_->RealSaveCfg(cfg);
}

TEST_F(AppCfgManagerTest, GenrateConfig) {
  static constexpr float kGenColdWaterTariff = 50.93;
  static constexpr float kGenHotWaterTariff = 165.47;
  static constexpr float kGenWaterSinkTariff = 39.97;
  static constexpr float kGenElectricityT1Tariff = 8.23;
  static constexpr float kGenElectricityT2Tariff = 2.62;
  static constexpr float kGenElectricityT3Tariff = 5.66;

  AppConfiguration expected_cfg;
  expected_cfg.SetColdWaterTariff(kGenColdWaterTariff);
  expected_cfg.SetHotWaterTariff(kGenHotWaterTariff);
  expected_cfg.SetWaterSinkTariff(kGenWaterSinkTariff);
  expected_cfg.SetElectricityT1Tariff(kGenElectricityT1Tariff);
  expected_cfg.SetElectricityT2Tariff(kGenElectricityT2Tariff);
  expected_cfg.SetElectricityT3Tariff(kGenElectricityT3Tariff);

  auto actually_cfg = appCfgManagerMock_->RealGenerateConfig();
  ASSERT_TRUE(actually_cfg);
  EXPECT_EQ(expected_cfg, *actually_cfg);
}

TEST_F(AppCfgManagerTest, CfgToString) {
  static constexpr float kColdWaterTariff = 50.93;
  static constexpr float kHotWaterTariff = 165.47;
  static constexpr float kWaterSinkTariff = 39.97;
  static constexpr float kElectricityT1Tariff = 8.23;
  static constexpr float kElectricityT2Tariff = 2.62;
  static constexpr float kElectricityT3Tariff = 5.66;

  static constexpr std::string_view kExpectedStr =
      "cold_water_tariff = 50.93\n"
      "hot_water_tariff = 165.47\n"
      "water_sink_tariff = 39.97\n"
      "electricity_t1_tariff = 8.23\n"
      "electricity_t2_tariff = 2.62\n"
      "electricity_t3_tariff = 5.66";

  AppConfiguration cfg;
  cfg.SetColdWaterTariff(kColdWaterTariff);
  cfg.SetHotWaterTariff(kHotWaterTariff);
  cfg.SetWaterSinkTariff(kWaterSinkTariff);
  cfg.SetElectricityT1Tariff(kElectricityT1Tariff);
  cfg.SetElectricityT2Tariff(kElectricityT2Tariff);
  cfg.SetElectricityT3Tariff(kElectricityT3Tariff);

  auto actually_str = appCfgManagerMock_->RealCfgToString(cfg);
  EXPECT_EQ(kExpectedStr, actually_str);
}

TEST_F(AppCfgManagerTest, StringToCfg) {
  static constexpr float kColdWaterTariff = 50.93;
  static constexpr float kHotWaterTariff = 165.47;
  static constexpr float kWaterSinkTariff = 39.97;
  static constexpr float kElectricityT1Tariff = 8.23;
  static constexpr float kElectricityT2Tariff = 2.62;
  static constexpr float kElectricityT3Tariff = 5.66;

  static constexpr std::string_view kStr =
      "cold_water_tariff = 50.93\n"
      "hot_water_tariff = 165.47\n"
      "water_sink_tariff = 39.97\n"
      "electricity_t1_tariff = 8.23\n"
      "electricity_t2_tariff = 2.62\n"
      "electricity_t3_tariff = 5.66";

  AppConfiguration expected_cfg;
  expected_cfg.SetColdWaterTariff(kColdWaterTariff);
  expected_cfg.SetHotWaterTariff(kHotWaterTariff);
  expected_cfg.SetWaterSinkTariff(kWaterSinkTariff);
  expected_cfg.SetElectricityT1Tariff(kElectricityT1Tariff);
  expected_cfg.SetElectricityT2Tariff(kElectricityT2Tariff);
  expected_cfg.SetElectricityT3Tariff(kElectricityT3Tariff);

  auto actually_cfg = appCfgManagerMock_->RealStringToCfg(kStr.data());
  EXPECT_EQ(expected_cfg, actually_cfg);
}

TEST_F(AppCfgManagerTest, SaveFilePassingArgs) {
  const std::filesystem::path kDirPath = "dir_path";
  const std::filesystem::path kFilename = "communal_calculator.conf";
  constexpr auto kFileFlags = std::fstream::out | std::ofstream::trunc;

  constexpr char const *kData = "123456789";
  constexpr int kDataSize = 9;

  auto file_path = kDirPath;
  file_path /= kFilename;

  EXPECT_CALL(stdOfStreamWrapperMock_, Open(file_path, kFileFlags));

  EXPECT_CALL(stdOfStreamWrapperMock_, IsOpen)
      .WillOnce(::testing::Return(true));

  EXPECT_CALL(stdOfStreamWrapperMock_,
              Write(::testing::StrEq(kData), kDataSize))
      .WillOnce(::testing::ReturnRef(stdOfStreamWrapperMock_));

  EXPECT_CALL(stdOfStreamWrapperMock_, Close);

  EXPECT_CALL(*appCfgManagerMock_, GetDirPath)
      .WillOnce(::testing::ReturnRef(kDirPath));

  appCfgManagerMock_->RealSaveFile(stdOfStreamWrapperMock_, kData, kDataSize);
}

TEST_F(AppCfgManagerTest, SaveFileIsOpenFalse) {
  const std::filesystem::path kDirPath = "dir_path";

  EXPECT_CALL(stdOfStreamWrapperMock_, Open);
  EXPECT_CALL(stdOfStreamWrapperMock_, IsOpen)
      .WillOnce(::testing::Return(false));

  EXPECT_CALL(*appCfgManagerMock_, GetDirPath)
      .WillOnce(::testing::ReturnRef(kDirPath));

  EXPECT_THROW(
      appCfgManagerMock_->RealSaveFile(stdOfStreamWrapperMock_, nullptr, 0),
      std::runtime_error);
}

}  // namespace CommunalCalculator::Core::Test
