#ifndef SOURCEFILES_MODEL_CORE_APP_CONFIGURATION_H_
#define SOURCEFILES_MODEL_CORE_APP_CONFIGURATION_H_

namespace CommunalCalculator::Core {

class AppConfiguration {
 public:
  AppConfiguration() = default;
  AppConfiguration(const AppConfiguration &) = default;
  AppConfiguration(AppConfiguration &&) = default;

  auto operator=(const AppConfiguration &) -> AppConfiguration & = default;
  auto operator=(AppConfiguration &&) -> AppConfiguration & = default;

  virtual ~AppConfiguration() = default;

  auto operator==(const AppConfiguration &right) const -> bool;

  virtual void SetColdWaterTariff(float value);
  [[nodiscard]] virtual auto GetColdWaterTariff() const -> float;

  virtual void SetHotWaterTariff(float value);
  [[nodiscard]] virtual auto GetHotWaterTariff() const -> float;

  virtual void SetWaterSinkTariff(float value);
  [[nodiscard]] virtual auto GetWaterSinkTariff() const -> float;

  virtual void SetElectricityT1Tariff(float value);
  [[nodiscard]] virtual auto GetElectricityT1Tariff() const -> float;

  virtual void SetElectricityT2Tariff(float value);
  [[nodiscard]] virtual auto GetElectricityT2Tariff() const -> float;

  virtual void SetElectricityT3Tariff(float value);
  [[nodiscard]] virtual auto GetElectricityT3Tariff() const -> float;

 private:
  float coldWaterTariff_{0};
  float hotWaterTariff_{0};
  float waterSinkTariff_{0};
  float electricityT1Tariff_{0};
  float electricityT2Tariff_{0};
  float electricityT3Tariff_{0};
};

}  // namespace CommunalCalculator::Core

#endif  // SOURCEFILES_MODEL_CORE_APP_CONFIGURATION_H_
