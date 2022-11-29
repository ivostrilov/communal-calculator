#ifndef SOURCEFILES_MODEL_CORE_WORKSPACE_H_
#define SOURCEFILES_MODEL_CORE_WORKSPACE_H_

#include <filesystem>
#include <string>

#include "wrappers/cstd_wrapper.h"

namespace CommunalCalculator::Core {

namespace Test {
class WorkspaceMock;
}

class Workspace {
 public:
  Workspace() = default;
  Workspace(const Workspace &) = default;
  Workspace(Workspace &&) = default;

  auto operator=(const Workspace &) -> Workspace & = default;
  auto operator=(Workspace &&) -> Workspace & = default;

  virtual ~Workspace() = default;

  virtual auto GetUserHomePath() -> std::filesystem::path;

 private:
  friend Test::WorkspaceMock;

  virtual auto GetEnvVarValue(Wrappers::CSTDWrapper &cstd_wrapper,
                              const char *var_name) -> std::string;
};

}  // namespace CommunalCalculator::Core

#endif  // SOURCEFILES_MODEL_CORE_WORKSPACE_H_
