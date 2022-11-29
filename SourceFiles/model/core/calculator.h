#ifndef SOURCEFILES_MODEL_CORE_CALCULATOR_H_
#define SOURCEFILES_MODEL_CORE_CALCULATOR_H_

#include <map>
#include <memory>
#include <string>

#include "core/communal_counter.h"

namespace CommunalCalculator::Core {

namespace Test {
class CalculatorMock;
}

class Calculator {
 public:
  using CommunalCounters =
      std::map<CommunalCounter::Type, std::shared_ptr<CommunalCounter>>;

  Calculator() = default;
  Calculator(const Calculator &) = default;
  Calculator(Calculator &&) = default;

  auto operator=(const Calculator &) -> Calculator & = default;
  auto operator=(Calculator &&) -> Calculator & = default;

  virtual ~Calculator() = default;

  virtual void SetWaterSinkTariff(float value);
  [[nodiscard]] virtual auto GetWaterSinkTariff() const -> float;

  virtual void SetCounter(const std::shared_ptr<CommunalCounter> &counter);
  [[nodiscard]] virtual auto GetCounters() const -> const CommunalCounters &;

  virtual auto CalculateSummary(std::string *calculation_log) -> float;
  virtual auto CalculateWaterSinkSummary(std::string *calculation_log) -> float;

 private:
  virtual auto ToString(float number) -> std::string;

  friend Test::CalculatorMock;

  float waterSinkTariff_{0};
  CommunalCounters counters_;
};

}  // namespace CommunalCalculator::Core

#endif  // SOURCEFILES_MODEL_CORE_CALCULATOR_H_
