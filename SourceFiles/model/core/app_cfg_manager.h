#ifndef SOURCEFILES_MODEL_CORE_APP_CFG_MANAGER_H_
#define SOURCEFILES_MODEL_CORE_APP_CFG_MANAGER_H_

#include <filesystem>
#include <memory>
#include <string>

#include "core/app_configuration.h"
#include "wrappers/std_of_stream_wrapper.h"

namespace CommunalCalculator::Core {

namespace Test {
class AppCfgManagerMock;
}

class AppCfgManager {
 public:
  AppCfgManager() = default;
  AppCfgManager(const AppCfgManager &) = default;
  AppCfgManager(AppCfgManager &&) = default;

  auto operator=(const AppCfgManager &) -> AppCfgManager & = default;
  auto operator=(AppCfgManager &&) -> AppCfgManager & = default;

  virtual ~AppCfgManager() = default;

  virtual void SetDirPath(const std::filesystem::path &dir_path);
  [[nodiscard]] virtual auto GetDirPath() const
      -> const std::filesystem::path &;

  [[nodiscard]] virtual auto GetCfg() -> std::shared_ptr<AppConfiguration>;
  virtual void SaveCfg(const std::shared_ptr<AppConfiguration> &cfg);

  [[nodiscard]] virtual auto GenerateConfig()
      -> std::shared_ptr<AppConfiguration>;

 private:
  friend Test::AppCfgManagerMock;

  static constexpr char const *kCfgFilename = "communal_calculator.conf";

  static constexpr float kGenColdWaterTariff = 50.93;
  static constexpr float kGenHotWaterTariff = 165.47;
  static constexpr float kGenWaterSinkTariff = 39.97;
  static constexpr float kGenElectricityT1Tariff = 8.23;
  static constexpr float kGenElectricityT2Tariff = 2.62;
  static constexpr float kGenElectricityT3Tariff = 5.66;

  static constexpr std::string_view kColdWaterTariffKey = "cold_water_tariff";
  static constexpr std::string_view kHotWaterTariffKey = "hot_water_tariff";
  static constexpr std::string_view kWaterSinkTariffKey = "water_sink_tariff";

  static constexpr std::string_view kElectricityT1TariffKey =
      "electricity_t1_tariff";
  static constexpr std::string_view kElectricityT2TariffKey =
      "electricity_t2_tariff";
  static constexpr std::string_view kElectricityT3TariffKey =
      "electricity_t3_tariff";

  virtual auto CfgToString(const AppConfiguration &cfg) -> std::string;
  virtual auto StringToCfg(const std::string &str) -> AppConfiguration;

  virtual void SaveFile(Wrappers::STDOfStreamWrapper &of_stream,
                        const char *data, size_t size);

  std::filesystem::path dirPath_;
};

}  // namespace CommunalCalculator::Core

#endif  // SOURCEFILES_MODEL_CORE_APP_CFG_MANAGER_H_
