#include "wrappers/std_of_stream_wrapper.h"

namespace CommunalCalculator::Wrappers {

void STDOfStreamWrapper::Open(const std::filesystem::path &filename,
                              std::ios_base::openmode mode) {
  std::ofstream::open(filename, mode);
}

void STDOfStreamWrapper::Close() { std::ofstream::close(); }

auto STDOfStreamWrapper::IsOpen() -> bool { return std::ofstream::is_open(); }

auto STDOfStreamWrapper::Write(const char *data, std::streamsize count)
    -> basic_ostream & {
  return std::ofstream::write(data, count);
}

}  // namespace CommunalCalculator::Wrappers
