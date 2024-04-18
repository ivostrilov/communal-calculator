#ifndef SOURCEFILES_MODEL_CORE_VALUES_HISTORY_MANAGER_H_
#define SOURCEFILES_MODEL_CORE_VALUES_HISTORY_MANAGER_H_

#include <filesystem>
#include <optional>
#include <string>

#include "core/values_history.h"
#include "wrappers/std_of_stream_wrapper.h"

namespace CommunalCalculator::Core {

class ValuesHistoryManager final {
 public:
  ValuesHistoryManager() = default;
  ValuesHistoryManager(const ValuesHistoryManager &) = default;
  ValuesHistoryManager(ValuesHistoryManager &&) = default;

  auto operator=(const ValuesHistoryManager &)
      -> ValuesHistoryManager & = default;
  auto operator=(ValuesHistoryManager &&) -> ValuesHistoryManager & = default;

  ~ValuesHistoryManager() = default;

  void SetDataDirPath(const std::filesystem::path &data_dir_path);

  void Save(const ValuesHistory &values_history);
  auto Read() -> std::optional<ValuesHistory>;

 private:
  static constexpr char const *kFilename = "communal_calculator.history";

  static constexpr std::string_view kColdWaterPreviousKey =
      "cold_water_previous";
  static constexpr std::string_view kColdWaterCurrentKey = "cold_water_current";

  static constexpr std::string_view kHotWaterPreviousKey = "hot_water_previous";
  static constexpr std::string_view kHotWaterCurrentKey = "hot_water_current";

  static constexpr std::string_view kElectricityT1PreviousKey =
      "electricity_t1_previous";
  static constexpr std::string_view kElectricityT1CurrentKey =
      "electricity_t1_current";

  static constexpr std::string_view kElectricityT2PreviousKey =
      "electricity_t2_previous";
  static constexpr std::string_view kElectricityT2CurrentKey =
      "electricity_t2_current";

  static constexpr std::string_view kElectricityT3PreviousKey =
      "electricity_t3_previous";
  static constexpr std::string_view kElectricityT3CurrentKey =
      "electricity_t3_current";

  virtual auto ValuesHistoryToString(const ValuesHistory &cfg) -> std::string;
  virtual auto StringToValuesHistory(const std::string &str) -> ValuesHistory;

  virtual void SaveFile(Wrappers::STDOfStreamWrapper &of_stream,
                        const char *data, size_t size);

  std::filesystem::path dataDirPath_;
};

}  // namespace CommunalCalculator::Core

#endif  // SOURCEFILES_MODEL_CORE_VALUES_HISTORY_MANAGER_H_
