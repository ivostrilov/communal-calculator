#include "core/values_history_manager.h"

#include <algorithm>
#include <filesystem>
#include <sstream>
#include <stdexcept>

namespace CommunalCalculator::Core {

void ValuesHistoryManager::SetDataDirPath(
    const std::filesystem::path &data_dir_path) {
  dataDirPath_ = data_dir_path;
}

void ValuesHistoryManager::Save(const ValuesHistory &values_history) {
  auto str = ValuesHistoryToString(values_history);

  Wrappers::STDOfStreamWrapper std_of_stream_wrapper;
  SaveFile(std_of_stream_wrapper, str.data(), str.size());
}

auto ValuesHistoryManager::Read() -> std::optional<ValuesHistory> {
  auto file_path = dataDirPath_;
  file_path /= kFilename;

  if (!std::filesystem::exists(file_path)) {
    return {};
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
  ValuesHistory values_history = StringToValuesHistory(str);

  return values_history;
}

auto ValuesHistoryManager::ValuesHistoryToString(const ValuesHistory &cfg)
    -> std::string {
  std::string str;

  auto add_value = [&str](const std::string_view &key, float value) {
    auto value_str = std::to_string(value);

    // Because std::to_string(165.47) = "165.470001"
    auto dot_pos = value_str.find('.');
    if (dot_pos != std::string::npos) {
      dot_pos += 4;
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

  add_value(kColdWaterPreviousKey, cfg.coldWaterPrevious);
  add_value(kColdWaterCurrentKey, cfg.coldWaterCurrent);
  add_value(kHotWaterPreviousKey, cfg.hotWaterPrevious);
  add_value(kHotWaterCurrentKey, cfg.hotWaterCurrent);
  add_value(kElectricityT1PreviousKey, cfg.electricityT1Previous);
  add_value(kElectricityT1CurrentKey, cfg.electricityT1Current);
  add_value(kElectricityT2PreviousKey, cfg.electricityT2Previous);
  add_value(kElectricityT2CurrentKey, cfg.electricityT2Current);
  add_value(kElectricityT3PreviousKey, cfg.electricityT3Previous);
  add_value(kElectricityT3CurrentKey, cfg.electricityT3Current);

  return str;
}

auto ValuesHistoryManager::StringToValuesHistory(const std::string &str)
    -> ValuesHistory {
  constexpr char kKeyValueSeparator = '=';

  ValuesHistory values_history;

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

    if (key_str == kColdWaterPreviousKey) {
      values_history.coldWaterPrevious = value_float;
    } else if (key_str == kColdWaterCurrentKey) {
      values_history.coldWaterCurrent = value_float;
    } else if (key_str == kHotWaterPreviousKey) {
      values_history.hotWaterPrevious = value_float;
    } else if (key_str == kHotWaterCurrentKey) {
      values_history.hotWaterCurrent = value_float;
    } else if (key_str == kElectricityT1PreviousKey) {
      values_history.electricityT1Previous = value_float;
    } else if (key_str == kElectricityT1CurrentKey) {
      values_history.electricityT1Current = value_float;
    } else if (key_str == kElectricityT2PreviousKey) {
      values_history.electricityT2Previous = value_float;
    } else if (key_str == kElectricityT2CurrentKey) {
      values_history.electricityT2Current = value_float;
    } else if (key_str == kElectricityT3PreviousKey) {
      values_history.electricityT3Previous = value_float;
    } else if (key_str == kElectricityT3CurrentKey) {
      values_history.electricityT3Current = value_float;
    }
  }

  return values_history;
}

void ValuesHistoryManager::SaveFile(Wrappers::STDOfStreamWrapper &of_stream,
                                    const char *data, size_t size) {
  constexpr auto kFileFlags = std::fstream::out | std::ofstream::trunc;

  auto file_path = dataDirPath_;
  file_path /= kFilename;

  of_stream.Open(file_path, kFileFlags);
  if (!of_stream.IsOpen()) {
    throw std::runtime_error(
        "AppCfgManager::SaveFile: of_stream.IsOpen() has returned false");
  }

  of_stream.Write(data, static_cast<long>(size));
  of_stream << std::endl;
  of_stream.Close();
}

}  // namespace CommunalCalculator::Core
