#ifndef TESTS_SOURCEFILES_WRAPPERS_STD_FILESYSTEM_WRAPPER_TEST_H
#define TESTS_SOURCEFILES_WRAPPERS_STD_FILESYSTEM_WRAPPER_TEST_H

#include <gmock/gmock.h>

#include "wrappers/std_filesystem_wrapper.h"

namespace CommunalCalculator::Wrappers::Test {

class STDFilesystemWrapperMock : public Wrappers::STDFilesystemWrapper {
 public:
  MOCK_METHOD(bool, CreateDirectories,
              (const std::filesystem::path &p, std::error_code &ec),
              (override));

  MOCK_METHOD(bool, Exists, (const std::filesystem::path &), (override));
};

}  // namespace CommunalCalculator::Wrappers::Test

#endif  // TESTS_SOURCEFILES_WRAPPERS_STD_FILESYSTEM_WRAPPER_TEST_H
