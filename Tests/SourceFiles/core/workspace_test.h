#ifndef TESTS_SOURCEFILES_CORE_WORKSPACE_TEST_H_
#define TESTS_SOURCEFILES_CORE_WORKSPACE_TEST_H_

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "core/workspace.h"
#include "wrappers/cstd_wrapper_test.h"

namespace CommunalCalculator::Core::Test {

class WorkspaceMock;

class WorkspaceTest : public ::testing::Test {
 public:
  void SetUp() override { workspaceMock_ = std::make_unique<WorkspaceMock>(); }

  std::unique_ptr<WorkspaceMock> workspaceMock_;
  Wrappers::Test::CSTDWrapperMock cstdWrapperMock_;
};

class WorkspaceMock : public Core::Workspace {
 public:
  MOCK_METHOD(std::filesystem::path, GetUserHomePath, (), (override));
  auto RealGetUserHomePath() -> std::filesystem::path {
    return Workspace::GetUserHomePath();
  }

  MOCK_METHOD(std::string, GetEnvVarValue,
              (Wrappers::CSTDWrapper & cstd_wrapper, const char *var_name),
              (override));
  auto RealGetEnvVarValue(Wrappers::CSTDWrapper &cstd_wrapper,
                          const char *var_name) -> std::string {
    return Workspace::GetEnvVarValue(cstd_wrapper, var_name);
  };
};

}  // namespace CommunalCalculator::Core::Test

#endif  // TESTS_SOURCEFILES_CORE_WORKSPACE_TEST_H_
