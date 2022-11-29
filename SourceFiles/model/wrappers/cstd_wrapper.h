#ifndef SOURCEFILES_MODEL_WRAPPERS_CSTD_WRAPPER_H_
#define SOURCEFILES_MODEL_WRAPPERS_CSTD_WRAPPER_H_

#include <cstdlib>

namespace CommunalCalculator::Wrappers {

class CSTDWrapper {
 public:
  CSTDWrapper() = default;
  CSTDWrapper(const CSTDWrapper &) = default;
  CSTDWrapper(CSTDWrapper &&) = default;

  auto operator=(const CSTDWrapper &) -> CSTDWrapper & = default;
  auto operator=(CSTDWrapper &&) -> CSTDWrapper & = default;

  virtual ~CSTDWrapper() = default;

  virtual auto GetEnv(const char *env_var) -> char *;
};

}  // namespace CommunalCalculator::Wrappers

#endif  // SOURCEFILES_MODEL_WRAPPERS_CSTD_WRAPPER_H_
