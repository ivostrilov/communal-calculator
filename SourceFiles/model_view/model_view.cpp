#include "model_view/model_view.h"

#include <cassert>
#include <iostream>
#include <utility>

#include "core/communal_counter.h"

namespace CommunalCalculator {

namespace {

auto GetFloat(const QMap<QString, QVariant> &values, const char *key) -> float {
  auto found = values.find(key);

  if (found != values.cend()) {
    const auto &variant = found.value();

    if (variant.canConvert<float>()) {
      return variant.toFloat();
    }
  }

  return 0;
}

}  // namespace

void ModelView::ConnectModel(const std::shared_ptr<Core::Model> &model_view) {
  model_ = model_view;
  assert(model_);

  auto on_calculation = [weak_self = weak_from_this()]() {
    auto self = weak_self.lock();
    if (!self) {
      return;
    }

    auto calculation = self->model_->calculationResultObserver_.PullCopy();

    QMap<QString, QVariant> calculation_map;
    calculation_map.insert("result", calculation.result);
    calculation_map.insert("log", QString(calculation.log.c_str()));

    self->EmitSummaryCalculated(calculation_map);
  };

  auto on_app_cfg_changed = [weak_self = weak_from_this()]() {
    auto self = weak_self.lock();
    if (!self) {
      return;
    }

    auto cfg_map = self->onGetAppConfiguration();
    self->EmitAppCfgChanged(cfg_map);
  };

  model_->calculationResultObserver_.SetConnection(std::move(on_calculation));
  model_->appConfigurationObserver_.SetConnection(
      std::move(on_app_cfg_changed));
}

auto ModelView::onGetAppConfiguration() -> QMap<QString, QVariant> {
  auto cfg = model_->appConfigurationObserver_.PullCopy();

  QMap<QString, QVariant> cfg_map;
  cfg_map.insert("coldWaterTariff", cfg.GetColdWaterTariff());
  cfg_map.insert("hotWaterTariff", cfg.GetHotWaterTariff());
  cfg_map.insert("waterSinkTariff", cfg.GetWaterSinkTariff());
  cfg_map.insert("T1Tariff", cfg.GetElectricityT1Tariff());
  cfg_map.insert("T2Tariff", cfg.GetElectricityT2Tariff());
  cfg_map.insert("T3Tariff", cfg.GetElectricityT3Tariff());

  return cfg_map;
}

void ModelView::onCalculateSummary(const QMap<QString, QVariant> &values) {
  constexpr auto kColdWaterType = Core::CommunalCounter::Type::kColdWater;
  constexpr auto kHotWaterType = Core::CommunalCounter::Type::kHotWater;
  constexpr auto kT1Type = Core::CommunalCounter::Type::kElectricityT1;
  constexpr auto kT2Type = Core::CommunalCounter::Type::kElectricityT2;
  constexpr auto kT3Type = Core::CommunalCounter::Type::kElectricityT3;

  auto app_cfg = model_->appConfigurationObserver_.PullCopy();

  auto cold_water = CreatCommunalCounter(kColdWaterType);
  cold_water->SetPrevValue(GetFloat(values, "coldWaterPrev"));
  cold_water->SetCurValue(GetFloat(values, "coldWaterCur"));
  cold_water->SetTariffValue(app_cfg.GetColdWaterTariff());

  auto hot_water = CreatCommunalCounter(kHotWaterType);
  hot_water->SetPrevValue(GetFloat(values, "hotWaterPrev"));
  hot_water->SetCurValue(GetFloat(values, "hotWaterCur"));
  hot_water->SetTariffValue(app_cfg.GetHotWaterTariff());

  auto electricity_t1 = CreatCommunalCounter(kT1Type);
  electricity_t1->SetPrevValue(GetFloat(values, "T1Prev"));
  electricity_t1->SetCurValue(GetFloat(values, "T1Cur"));
  electricity_t1->SetTariffValue(app_cfg.GetElectricityT1Tariff());

  auto electricity_t2 = CreatCommunalCounter(kT2Type);
  electricity_t2->SetPrevValue(GetFloat(values, "T2Prev"));
  electricity_t2->SetCurValue(GetFloat(values, "T2Cur"));
  electricity_t2->SetTariffValue(app_cfg.GetElectricityT2Tariff());

  auto electricity_t3 = CreatCommunalCounter(kT3Type);
  electricity_t3->SetPrevValue(GetFloat(values, "T3Prev"));
  electricity_t3->SetCurValue(GetFloat(values, "T3Cur"));
  electricity_t3->SetTariffValue(app_cfg.GetElectricityT3Tariff());

  Core::Calculator::CommunalCounters communal_counters = {
      {kColdWaterType, std::move(cold_water)},
      {kHotWaterType, std::move(hot_water)},
      {kT1Type, std::move(electricity_t1)},
      {kT2Type, std::move(electricity_t2)},
      {kT3Type, std::move(electricity_t3)}};

  model_->CalculateSummary(std::move(communal_counters));
}

void ModelView::onAppCfgChanged(const QMap<QString, QVariant> &values) {
  float cold_water = GetFloat(values, "coldWaterTariff");
  float hot_water = GetFloat(values, "hotWaterTariff");
  float sink_water = GetFloat(values, "sinkWaterTariff");
  float electricity_t1 = GetFloat(values, "T1Tariff");
  float electricity_t2 = GetFloat(values, "T2Tariff");
  float electricity_t3 = GetFloat(values, "T3Tariff");

  Core::AppConfiguration app_cfg = model_->appConfigurationObserver_.PullCopy();
  app_cfg.SetColdWaterTariff(cold_water);
  app_cfg.SetHotWaterTariff(hot_water);
  app_cfg.SetWaterSinkTariff(sink_water);
  app_cfg.SetElectricityT1Tariff(electricity_t1);
  app_cfg.SetElectricityT2Tariff(electricity_t2);
  app_cfg.SetElectricityT3Tariff(electricity_t3);

  model_->ChangeAppConfiguration(app_cfg);
}

auto ModelView::CreatCommunalCounter(Core::CommunalCounter::Type type)
    -> std::shared_ptr<Core::CommunalCounter> {
  return std::make_shared<Core::CommunalCounter>(type);
}

void ModelView::EmitSummaryCalculated(const QMap<QString, QVariant> &result) {
  emit summaryCalculated(result);
}

void ModelView::EmitAppCfgChanged(const QMap<QString, QVariant> &cfg) {
  emit appCfgChanged(cfg);
}

}  // namespace CommunalCalculator
