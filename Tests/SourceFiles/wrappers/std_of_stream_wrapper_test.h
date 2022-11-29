#ifndef TESTS_SOURCEFILES_WRAPPERS_STD_OF_STREAM_WRAPPER_TEST_H_
#define TESTS_SOURCEFILES_WRAPPERS_STD_OF_STREAM_WRAPPER_TEST_H_

#include <gmock/gmock.h>

#include "wrappers/std_of_stream_wrapper.h"

namespace CommunalCalculator::Wrappers::Test {

class STDOfStreamWrapperMock : public Wrappers::STDOfStreamWrapper {
 public:
  MOCK_METHOD(void, Open,
              (const std::filesystem::path &filename,
               std::ios_base::openmode mode),
              (override));

  MOCK_METHOD(void, Close, (), (override));

  MOCK_METHOD(bool, IsOpen, (), (override));

  MOCK_METHOD(std::basic_ostream<char> &, Write,
              (const char *data, std::streamsize count), (override));
};

}  // namespace CommunalCalculator::Wrappers::Test

#endif  // TESTS_SOURCEFILES_WRAPPERS_STD_OF_STREAM_WRAPPER_TEST_H_
