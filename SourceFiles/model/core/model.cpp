#include "core/model.h"

#include <memory>
#include <utility>

namespace CommunalCalculator::Core {

void Model::Initialize() {
  Workspace workspace;
  Wrappers::STDFilesystemWrapper std_filesystem_wrapper;
  InitializeConfig(appCfgManager_, workspace, std_filesystem_wrapper);
}

void Model::CalculateSummary(Calculator::CommunalCounters &&counters) {
  Calculator calculator;
  Calculate(calculator, counters);
}

void Model::ChangeAppConfiguration(const AppConfiguration &app_cfg) {
  auto ptr = std::make_shared<AppConfiguration>(app_cfg);
  appCfgManager_.SaveCfg(ptr);

  appConfigurationObserver_.Push(app_cfg);
}

void Model::Calculate(Calculator &calculator,
                      const Calculator::CommunalCounters &counters) {
  for (const auto &counter_it : counters) {
    calculator.SetCounter(counter_it.second);
  }

  auto app_cfg = appConfigurationObserver_.PullCopy();
  auto water_sink_tariff = app_cfg.GetWaterSinkTariff();

  calculator.SetWaterSinkTariff(water_sink_tariff);

  Calculation calculation;
  calculation.result = calculator.CalculateSummary(&calculation.log);

  calculationResultObserver_.Push(std::move(calculation));
}

void Model::InitializeConfig(
    AppCfgManager &app_cfg_manager, Workspace &workspace,
    Wrappers::STDFilesystemWrapper &filesystem_wrapper) {
  auto config_dir_path = workspace.GetUserHomePath();
  config_dir_path /= kConfigDataDir;

  if (!filesystem_wrapper.Exists(config_dir_path)) {
    std::error_code error_code;
    bool created =
        filesystem_wrapper.CreateDirectories(config_dir_path, error_code);

    if (!created) {
      std::string msg =
          "Model::InitializeConfig: CreateDirectories returned false, error "
          "message: ";
      msg += error_code.message();
      throw std::runtime_error(msg);
    }
  }

  app_cfg_manager.SetDirPath(config_dir_path);

  auto cfg = app_cfg_manager.GetCfg();
  if (cfg) {
    appConfigurationObserver_.Push(*cfg);
    return;
  }

  cfg = app_cfg_manager.GenerateConfig();
  app_cfg_manager.SaveCfg(cfg);
  appConfigurationObserver_.Push(*cfg);
}

}  // namespace CommunalCalculator::Core
