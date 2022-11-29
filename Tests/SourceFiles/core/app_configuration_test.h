#ifndef TESTS_SOURCEFILES_CORE_APP_CONFIGURATION_TEST_H_
#define TESTS_SOURCEFILES_CORE_APP_CONFIGURATION_TEST_H_

#include <gmock/gmock.h>

#include "core/app_configuration.h"

namespace CommunalCalculator::Core::Test {

class AppConfigurationMock : public Core::AppConfiguration {
 public:
  MOCK_METHOD(void, SetColdWaterTariff, (float value), (override));
  MOCK_METHOD(float, GetColdWaterTariff, (), (const override));

  MOCK_METHOD(void, SetHotWaterTariff, (float value), (override));
  MOCK_METHOD(float, GetHotWaterTariff, (), (const override));

  MOCK_METHOD(void, SetWaterSinkTariff, (float value), (override));
  MOCK_METHOD(float, GetWaterSinkTariff, (), (const override));

  MOCK_METHOD(void, SetElectricityT1Tariff, (float value), (override));
  MOCK_METHOD(float, GetElectricityT1Tariff, (), (const override));

  MOCK_METHOD(void, SetElectricityT2Tariff, (float value), (override));
  MOCK_METHOD(float, GetElectricityT2Tariff, (), (const override));

  MOCK_METHOD(void, SetElectricityT3Tariff, (float value), (override));
  MOCK_METHOD(float, GetElectricityT3Tariff, (), (const override));
};

}  // namespace CommunalCalculator::Core::Test

#endif  // TESTS_SOURCEFILES_CORE_APP_CONFIGURATION_TEST_H_
