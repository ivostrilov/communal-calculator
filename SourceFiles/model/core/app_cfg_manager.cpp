#include "core/app_cfg_manager.h"

#include <algorithm>
#include <filesystem>
#include <sstream>
#include <stdexcept>

namespace CommunalCalculator::Core {

void AppCfgManager::SetDirPath(const std::filesystem::path &dir_path) {
  dirPath_ = dir_path;
}

auto AppCfgManager::GetDirPath() const -> const std::filesystem::path & {
  return dirPath_;
}

auto AppCfgManager::GetCfg() -> std::shared_ptr<AppConfiguration> {
  auto file_path = GetDirPath();
  file_path /= kCfgFilename;

  if (!std::filesystem::exists(file_path)) {
    return nullptr;
  }

  std::ifstream file;
  file.open(file_path);
  if (!file.is_open()) {
    std::string msg = "Error: unable to open \"";
    msg += file_path.u8string();
    msg += "\"";
    throw std::runtime_error(msg);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  auto str = buffer.str();
  AppConfiguration cfg = StringToCfg(str);

  return std::make_shared<AppConfiguration>(cfg);
}

void AppCfgManager::SaveCfg(const std::shared_ptr<AppConfiguration> &cfg) {
  auto cfg_str = CfgToString(*cfg);

  Wrappers::STDOfStreamWrapper std_of_stream_wrapper;
  SaveFile(std_of_stream_wrapper, cfg_str.data(), cfg_str.size());
}

auto AppCfgManager::GenerateConfig() -> std::shared_ptr<AppConfiguration> {
  auto cfg = std::make_shared<AppConfiguration>();

  cfg->SetColdWaterTariff(kGenColdWaterTariff);
  cfg->SetHotWaterTariff(kGenHotWaterTariff);
  cfg->SetWaterSinkTariff(kGenWaterSinkTariff);
  cfg->SetElectricityT1Tariff(kGenElectricityT1Tariff);
  cfg->SetElectricityT2Tariff(kGenElectricityT2Tariff);
  cfg->SetElectricityT3Tariff(kGenElectricityT3Tariff);

  return cfg;
}

auto AppCfgManager::CfgToString(const AppConfiguration &cfg) -> std::string {
  std::string str;

  auto add_value = [&str](const std::string_view &key, float value) {
    auto value_str = std::to_string(value);

    // Because std::to_string(165.47) = "165.470001"
    auto dot_pos = value_str.find('.');
    if (dot_pos != std::string::npos) {
      dot_pos += 3;
      if (dot_pos < value_str.size()) {
        value_str.erase(dot_pos);
      }

      while (value_str.back() == '0') {
        value_str.pop_back();
      }

      if (value_str.back() == '.') {
        value_str.pop_back();
      }
    }

    if (!str.empty()) {
      str += "\n";
    }
    str += key;
    str += " = ";
    str += value_str;
  };

  add_value(kColdWaterTariffKey, cfg.GetColdWaterTariff());
  add_value(kHotWaterTariffKey, cfg.GetHotWaterTariff());
  add_value(kWaterSinkTariffKey, cfg.GetWaterSinkTariff());
  add_value(kElectricityT1TariffKey, cfg.GetElectricityT1Tariff());
  add_value(kElectricityT2TariffKey, cfg.GetElectricityT2Tariff());
  add_value(kElectricityT3TariffKey, cfg.GetElectricityT3Tariff());

  return str;
}

auto AppCfgManager::StringToCfg(const std::string &str) -> AppConfiguration {
  constexpr char kKeyValueSeparator = '=';

  AppConfiguration cfg;

  std::istringstream istringstream(str);
  std::string line;
  while (std::getline(istringstream, line)) {
    line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

    auto separator_pos = line.find(kKeyValueSeparator);
    if (separator_pos == std::string::npos) {
      continue;
    }

    auto key_str = line.substr(0, separator_pos);
    auto value_str = line.substr(separator_pos + 1);
    float value_float = 0.0;
    try {
      value_float = std::stof(value_str);
    } catch (...) {
      continue;
    }

    if (key_str == kColdWaterTariffKey) {
      cfg.SetColdWaterTariff(value_float);
    } else if (key_str == kHotWaterTariffKey) {
      cfg.SetHotWaterTariff(value_float);
    } else if (key_str == kWaterSinkTariffKey) {
      cfg.SetWaterSinkTariff(value_float);
    } else if (key_str == kElectricityT1TariffKey) {
      cfg.SetElectricityT1Tariff(value_float);
    } else if (key_str == kElectricityT2TariffKey) {
      cfg.SetElectricityT2Tariff(value_float);
    } else if (key_str == kElectricityT3TariffKey) {
      cfg.SetElectricityT3Tariff(value_float);
    }
  }

  return cfg;
}

void AppCfgManager::SaveFile(Wrappers::STDOfStreamWrapper &of_stream,
                             const char *data, size_t size) {
  constexpr auto kFileFlags = std::fstream::out | std::ofstream::trunc;

  auto file_path = GetDirPath();
  file_path /= kCfgFilename;

  of_stream.Open(file_path, kFileFlags);
  if (!of_stream.IsOpen()) {
    throw std::runtime_error(
        "AppCfgManager::SaveFile: of_stream.IsOpen() has returned false");
  }

  of_stream.Write(data, static_cast<long>(size));
  of_stream.Close();
}

}  // namespace CommunalCalculator::Core
