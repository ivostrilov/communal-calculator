#include "core/calculator.h"

#include <cassert>
#include <utility>

namespace CommunalCalculator::Core {

void Calculator::SetWaterSinkTariff(float value) { waterSinkTariff_ = value; }

auto Calculator::GetWaterSinkTariff() const -> float {
  return waterSinkTariff_;
}

void Calculator::SetCounter(const std::shared_ptr<CommunalCounter> &counter) {
  auto type = counter->GetType();
  counters_.insert_or_assign(type, counter);
}

auto Calculator::GetCounters() const -> const CommunalCounters & {
  return counters_;
}

auto Calculator::CalculateSummary(std::string *calculation_log) -> float {
  std::string result_log;
  float result = 0;

  const auto &counters = GetCounters();

  for (const auto &counter_it : counters) {
    const auto &counter = counter_it.second;
    assert(counter);

    auto name = counter->GetName();
    auto prev = counter->GetPrevValue();
    auto cur = counter->GetCurValue();
    auto tariff = counter->GetTariffValue();

    auto diff = std::fabs(cur - prev);
    auto summary = diff * tariff;

    result_log += result_log.empty() ? "" : "\n";
    result_log += name;
    result_log += ": |";
    result_log += ToString(cur);
    result_log += " - ";
    result_log += ToString(prev);
    result_log += "| * ";
    result_log += ToString(tariff);
    result_log += " = ";
    result_log += ToString(summary);

    result += summary;
  }

  std::string water_sink_log;
  auto water_sink_summary = CalculateWaterSinkSummary(&water_sink_log);

  result += water_sink_summary;

  if (!water_sink_log.empty()) {
    result_log += result_log.empty() ? "" : "\n";
    result_log += water_sink_log;
  }

  if (calculation_log != nullptr) {
    *calculation_log = std::move(result_log);
  }

  return result;
}

auto Calculator::CalculateWaterSinkSummary(std::string *calculation_log)
    -> float {
  constexpr char const *kCalculationLogPrefix = "Water Sink:";
  constexpr auto kColdWaterType = CommunalCounter::Type::kColdWater;
  constexpr auto kHotWaterType = CommunalCounter::Type::kHotWater;

  auto water_sink_tariff = GetWaterSinkTariff();

  std::string result_log;
  float result = 0;

  result_log += kCalculationLogPrefix;

  const auto &counters = GetCounters();

  auto cold_water_it = counters.find(kColdWaterType);
  bool cold_water_exist = cold_water_it != counters.cend();

  if (cold_water_exist) {
    const auto &counter = cold_water_it->second;
    assert(counter);

    auto prev = counter->GetPrevValue();
    auto cur = counter->GetCurValue();

    auto diff = std::fabs(cur - prev);
    auto summary = diff * water_sink_tariff;

    result += summary;

    result_log += " |";
    result_log += ToString(cur);
    result_log += " - ";
    result_log += ToString(prev);
    result_log += "| * ";
    result_log += ToString(water_sink_tariff);
  }

  auto hot_water_it = counters.find(kHotWaterType);
  if (hot_water_it != counters.cend()) {
    const auto &counter = hot_water_it->second;
    assert(counter);

    auto prev = counter->GetPrevValue();
    auto cur = counter->GetCurValue();

    auto diff = std::fabs(cur - prev);
    auto summary = diff * water_sink_tariff;

    result += summary;

    result_log += cold_water_exist ? " +" : "";
    result_log += " |";
    result_log += ToString(cur);
    result_log += " - ";
    result_log += ToString(prev);
    result_log += "| * ";
    result_log += ToString(water_sink_tariff);
  }

  result_log += " = ";
  result_log += ToString(result);

  if (calculation_log != nullptr) {
    *calculation_log = std::move(result_log);
  }

  return result;
}

auto Calculator::ToString(float number) -> std::string {
  constexpr int kPrecision = 100;
  constexpr int kReserveSize = 16;

  int integer = std::floor(number);

  auto fractional_float =
      std::round(std::fabs(number - static_cast<float>(integer)) * kPrecision);

  int fractional_int = static_cast<int>(fractional_float);

  std::string str;
  str.reserve(kReserveSize);

  str = std::to_string(integer);
  if (fractional_int == 0) {
    return str;
  }

  str += ".";
  str += std::to_string(fractional_int);

  str.erase(std::find_if(str.rbegin(), str.rend(),
                         [](unsigned char symbol) { return symbol != '0'; })
                .base(),
            str.end());

  return str;
}

}  // namespace CommunalCalculator::Core
