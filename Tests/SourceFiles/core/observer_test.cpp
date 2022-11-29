#include "core/observer_test.h"

namespace CommunalCalculator::Core::Test {

TEST_F(ObserverTest, PushPull) {
  constexpr int kTestValue = 100;

  bool connection_called = false;
  Observer<int> observer_int;

  auto connection = [kTestValue, &connection_called, &observer_int]() {
    connection_called = true;
    EXPECT_EQ(kTestValue, observer_int.PullCopy());
  };

  observer_int.SetConnection(connection);
  observer_int.Push(kTestValue);

  EXPECT_TRUE(connection_called);
}

}  // namespace CommunalCalculator::Core::Test
