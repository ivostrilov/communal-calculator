#ifndef SOURCEFILES_MODEL_CORE_MODEL_H_
#define SOURCEFILES_MODEL_CORE_MODEL_H_

#include <filesystem>
#include <string>

#include "core/app_cfg_manager.h"
#include "core/app_configuration.h"
#include "core/calculator.h"
#include "core/observer.h"
#include "core/values_history_manager.h"
#include "core/workspace.h"
#include "wrappers/std_filesystem_wrapper.h"

namespace CommunalCalculator::Core {

namespace Test {
class ModelMock;
}

class Model {
 public:
  struct Calculation {
    float result{0};
    std::string log;
  };

  Model() = default;
  Model(const Model &) = delete;
  Model(Model &&) = delete;

  auto operator=(const Model &) -> Model & = delete;
  auto operator=(Model &&) -> Model & = delete;

  virtual ~Model() = default;

  Observer<Calculation> calculationResultObserver_;
  Observer<AppConfiguration> appConfigurationObserver_;

  virtual void Initialize(const std::filesystem::path &app_data_path);
  virtual void CalculateSummary(Calculator::CommunalCounters &&counters);
  virtual void ChangeAppConfiguration(const AppConfiguration &app_cfg);
  virtual void SaveValuesHistory(const ValuesHistory &values_history);
  virtual auto ReadValuesHistory() -> ValuesHistory;

 private:
  friend Test::ModelMock;

  virtual void InitializeConfig(
      AppCfgManager &app_cfg_manager, Workspace &workspace,
      Wrappers::STDFilesystemWrapper &filesystem_wrapper);

  virtual void InitializeAppDataDir(
      ValuesHistoryManager &values_history_manager,
      Wrappers::STDFilesystemWrapper &filesystem_wrapper,
      const std::filesystem::path &app_data_path);

  virtual void Calculate(Calculator &calculator,
                         const Calculator::CommunalCounters &counters);

  // Final path will be '/home/$USER/' + kConfigDataDir (MacOS)
  static constexpr std::string_view kConfigDataDir =
      ".config/CommunalCalculator";

  // Final path will be
  // /home/$USER/Library/Application\ Support/ + kAppDataDirName (MacOS)
  static constexpr std::string_view kAppDataDirName = "CommunalCalculator";

  AppCfgManager appCfgManager_;
  ValuesHistoryManager valuesHistoryManager_;
};

}  // namespace CommunalCalculator::Core

#endif  // SOURCEFILES_MODEL_CORE_MODEL_H_
