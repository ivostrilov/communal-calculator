#ifndef SOURCEFILES_MODEL_CORE_COMMUNAL_COUNTER_H_
#define SOURCEFILES_MODEL_CORE_COMMUNAL_COUNTER_H_

#include <string>

namespace CommunalCalculator::Core {

class CommunalCounter {
 public:
  enum class Type {
    kNone = 0,
    kColdWater,
    kHotWater,
    kElectricityT1,
    kElectricityT2,
    kElectricityT3
  };

  CommunalCounter() = default;
  CommunalCounter(const CommunalCounter &) = default;
  CommunalCounter(CommunalCounter &&) = default;

  explicit CommunalCounter(Type type);
  explicit CommunalCounter(Type type, float prev_value, float cur_value,
                           float tariff_value);

  auto operator=(const CommunalCounter &) -> CommunalCounter & = default;
  auto operator=(CommunalCounter &&) -> CommunalCounter & = default;

  virtual ~CommunalCounter() = default;

  virtual void SetType(Type type);
  [[nodiscard]] virtual auto GetType() const -> Type;

  virtual void SetPrevValue(float value);
  [[nodiscard]] virtual auto GetPrevValue() const -> float;

  virtual void SetCurValue(float value);
  [[nodiscard]] virtual auto GetCurValue() const -> float;

  virtual void SetTariffValue(float value);
  [[nodiscard]] virtual auto GetTariffValue() const -> float;

  [[nodiscard]] virtual auto GetName() -> std::string;

 private:
  Type type_{Type::kNone};
  float prevValue_{0};
  float curValue_{0};
  float tariff_{0};
};

}  // namespace CommunalCalculator::Core

#endif  // SOURCEFILES_MODEL_CORE_COMMUNAL_COUNTER_H_
