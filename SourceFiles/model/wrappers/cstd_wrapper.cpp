#include "wrappers/cstd_wrapper.h"

namespace CommunalCalculator::Wrappers {

auto CSTDWrapper::GetEnv(const char *env_var) -> char * {
  return std::getenv(env_var);
}

}  // namespace CommunalCalculator::Wrappers
