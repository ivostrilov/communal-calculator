#include "core/communal_counter.h"

namespace CommunalCalculator::Core {

CommunalCounter::CommunalCounter(Type type) : type_(type) {}

CommunalCounter::CommunalCounter(Type type, float prev_value, float cur_value,
                                 float tariff_value)
    : type_(type),
      prevValue_(prev_value),
      curValue_(cur_value),
      tariff_(tariff_value) {}

void CommunalCounter::SetType(Type type) { type_ = type; }

auto CommunalCounter::GetType() const -> Type { return type_; }

void CommunalCounter::SetPrevValue(float value) { prevValue_ = value; }

auto CommunalCounter::GetPrevValue() const -> float { return prevValue_; }

void CommunalCounter::SetCurValue(float value) { curValue_ = value; }

auto CommunalCounter::GetCurValue() const -> float { return curValue_; }

void CommunalCounter::SetTariffValue(float value) { tariff_ = value; }

auto CommunalCounter::GetTariffValue() const -> float { return tariff_; }

auto CommunalCounter::GetName() -> std::string {
  switch (type_) {
    case Type::kNone: {
      return "None";
    }
    case Type::kHotWater: {
      return "Hot Water";
    }
    case Type::kColdWater: {
      return "Cold Water";
    }
    case Type::kElectricityT1: {
      return "Electricity T1";
    }
    case Type::kElectricityT2: {
      return "Electricity T2";
    }
    case Type::kElectricityT3: {
      return "Electricity T3";
    }
  }

  return "UNKNOWN";
}

}  // namespace CommunalCalculator::Core
