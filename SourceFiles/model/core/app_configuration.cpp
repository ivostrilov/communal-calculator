#include "core/app_configuration.h"

namespace CommunalCalculator::Core {

auto AppConfiguration::operator==(
    const CommunalCalculator::Core::AppConfiguration &right) const -> bool {
  return coldWaterTariff_ == right.coldWaterTariff_ &&
         hotWaterTariff_ == right.hotWaterTariff_ &&
         waterSinkTariff_ == right.waterSinkTariff_ &&
         electricityT1Tariff_ == right.electricityT1Tariff_ &&
         electricityT2Tariff_ == right.electricityT2Tariff_ &&
         electricityT3Tariff_ == right.electricityT3Tariff_;
}

void AppConfiguration::SetColdWaterTariff(float value) {
  coldWaterTariff_ = value;
}

auto AppConfiguration::GetColdWaterTariff() const -> float {
  return coldWaterTariff_;
}

void AppConfiguration::SetHotWaterTariff(float value) {
  hotWaterTariff_ = value;
}

auto AppConfiguration::GetHotWaterTariff() const -> float {
  return hotWaterTariff_;
}

void AppConfiguration::SetWaterSinkTariff(float value) {
  waterSinkTariff_ = value;
}

auto AppConfiguration::GetWaterSinkTariff() const -> float {
  return waterSinkTariff_;
}

void AppConfiguration::SetElectricityT1Tariff(float value) {
  electricityT1Tariff_ = value;
}

auto AppConfiguration::GetElectricityT1Tariff() const -> float {
  return electricityT1Tariff_;
}

void AppConfiguration::SetElectricityT2Tariff(float value) {
  electricityT2Tariff_ = value;
}

auto AppConfiguration::GetElectricityT2Tariff() const -> float {
  return electricityT2Tariff_;
}

void AppConfiguration::SetElectricityT3Tariff(float value) {
  electricityT3Tariff_ = value;
}

auto AppConfiguration::GetElectricityT3Tariff() const -> float {
  return electricityT3Tariff_;
}

}  // namespace CommunalCalculator::Core
