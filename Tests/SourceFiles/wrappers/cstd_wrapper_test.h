#ifndef TESTS_SOURCEFILES_WRAPPERS_CSTD_WRAPPER_TEST_H_
#define TESTS_SOURCEFILES_WRAPPERS_CSTD_WRAPPER_TEST_H_

#include <gmock/gmock.h>

#include "wrappers/cstd_wrapper.h"

namespace CommunalCalculator::Wrappers::Test {

class CSTDWrapperMock : public CSTDWrapper {
 public:
  MOCK_METHOD(char *, GetEnv, (const char *env_var), (override));
};

}  // namespace CommunalCalculator::Wrappers::Test

#endif  // TESTS_SOURCEFILES_WRAPPERS_CSTD_WRAPPER_TEST_H_
