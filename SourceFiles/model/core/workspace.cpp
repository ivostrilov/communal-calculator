#include "core/workspace.h"

#include <stdexcept>

#include "wrappers/cstd_wrapper.h"

namespace CommunalCalculator::Core {

auto Workspace::GetUserHomePath() -> std::filesystem::path {
  char const *env_var = nullptr;

#ifdef __APPLE__
  env_var = "HOME";
#else
  throw std::runtime_error("Workspace::GetUserHomePath: no implementation");
#endif

  Wrappers::CSTDWrapper cstd_wrapper;
  auto home_value = GetEnvVarValue(cstd_wrapper, env_var);

  return home_value;
}

auto Workspace::GetEnvVarValue(Wrappers::CSTDWrapper &cstd_wrapper,
                               const char *var_name) -> std::string {
  auto *value = cstd_wrapper.GetEnv(var_name);
  if (value == nullptr) {
    throw std::runtime_error(
        "Workspace::GetEnvVarValue: cstd_wrapper.GetEnv(var_name) has returned "
        "nullptr");
  }

  return value;
}

}  // namespace CommunalCalculator::Core
