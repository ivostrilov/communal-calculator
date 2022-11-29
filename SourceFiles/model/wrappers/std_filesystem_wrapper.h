#ifndef SOURCEFILES_MODEL_WRAPPERS_STD_FILESYSTEM_WRAPPER_H_
#define SOURCEFILES_MODEL_WRAPPERS_STD_FILESYSTEM_WRAPPER_H_

#include <filesystem>

namespace CommunalCalculator::Wrappers {

class STDFilesystemWrapper {
 public:
  STDFilesystemWrapper() = default;
  STDFilesystemWrapper(const STDFilesystemWrapper &) = default;
  STDFilesystemWrapper(STDFilesystemWrapper &&) = default;

  auto operator=(const STDFilesystemWrapper &)
      -> STDFilesystemWrapper & = default;
  auto operator=(STDFilesystemWrapper &&) -> STDFilesystemWrapper & = default;

  virtual ~STDFilesystemWrapper() = default;

  virtual auto CreateDirectories(const std::filesystem::path &p,
                                 std::error_code &ec) -> bool;

  virtual auto Exists(const std::filesystem::path &p) -> bool;
};

}  // namespace CommunalCalculator::Wrappers

#endif  // SOURCEFILES_MODEL_WRAPPERS_STD_FILESYSTEM_WRAPPER_H_
