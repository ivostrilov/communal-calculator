#ifndef TESTS_SOURCEFILES_CORE_COMMUNAL_COUNTER_TEST_H_
#define TESTS_SOURCEFILES_CORE_COMMUNAL_COUNTER_TEST_H_

#include <gmock/gmock.h>

#include <string>

#include "core/communal_counter.h"

namespace CommunalCalculator::Core::Test {

class CommunalCounterMock : public CommunalCounter {
 public:
  MOCK_METHOD(void, SetType, (Type type), (override));
  MOCK_METHOD(Type, GetType, (),  (const override));

  MOCK_METHOD(void, SetPrevValue, (float value), (override));
  MOCK_METHOD(float, GetPrevValue, (),  (const override));

  MOCK_METHOD(void, SetCurValue, (float value), (override));
  MOCK_METHOD(float, GetCurValue, (),  (const override));

  MOCK_METHOD(void, SetTariffValue, (float value), (override));
  MOCK_METHOD(float, GetTariffValue, (),  (const override));

  MOCK_METHOD(std::string, GetName, (), (override));
};

}  // namespace CommunalCalculator::Core::Test

#endif  // TESTS_SOURCEFILES_CORE_COMMUNAL_COUNTER_TEST_H_
