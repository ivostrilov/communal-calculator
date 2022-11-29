#include "wrappers/std_filesystem_wrapper.h"

namespace CommunalCalculator::Wrappers {

auto STDFilesystemWrapper::CreateDirectories(const std::filesystem::path &p,
                                             std::error_code &ec) -> bool {
  return std::filesystem::create_directories(p, ec);
}

auto STDFilesystemWrapper::Exists(const std::filesystem::path &p) -> bool {
  return std::filesystem::exists(p);
}

}  // namespace CommunalCalculator::Wrappers
