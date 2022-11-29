#include "core/workspace_test.h"

#include <stdexcept>

namespace CommunalCalculator::Core::Test {

TEST_F(WorkspaceTest, GetUserHomePathPassingArgs) {
  char const *env_var = nullptr;

#ifdef __APPLE__
  env_var = "HOME";
#else
  FAIL();
#endif

  EXPECT_CALL(*workspaceMock_,
              GetEnvVarValue(::testing::_, ::testing::StrEq(env_var)));

  workspaceMock_->RealGetUserHomePath();
}

TEST_F(WorkspaceTest, GetUserHomePathReturnValue) {
  constexpr char const *kHomePath = "(home path)";

  EXPECT_CALL(*workspaceMock_, GetEnvVarValue)
      .WillOnce(::testing::Return(kHomePath));

  auto actually = workspaceMock_->RealGetUserHomePath();
  EXPECT_EQ(kHomePath, actually);
}

TEST_F(WorkspaceTest, GetEnvVarValuePassingArgs) {
  constexpr char const *kEnvVar = "(env var)";

  EXPECT_CALL(cstdWrapperMock_, GetEnv(::testing::StrEq(kEnvVar)))
      .WillOnce(::testing::Return(const_cast<char *>(kEnvVar)));

  workspaceMock_->RealGetEnvVarValue(cstdWrapperMock_, kEnvVar);
}

TEST_F(WorkspaceTest, GetEnvVarValueReturnValue) {
  constexpr char const *kVarValue = "(var value)";

  EXPECT_CALL(cstdWrapperMock_, GetEnv)
      .WillOnce(::testing::Return(const_cast<char *>(kVarValue)));

  auto actually = workspaceMock_->RealGetEnvVarValue(cstdWrapperMock_, nullptr);
  EXPECT_EQ(kVarValue, actually);
}

TEST_F(WorkspaceTest, GetEnvVarValueCatchNullptrVal) {
  EXPECT_CALL(cstdWrapperMock_, GetEnv).WillOnce(::testing::ReturnNull());

  EXPECT_THROW(workspaceMock_->RealGetEnvVarValue(cstdWrapperMock_, nullptr),
               std::runtime_error);
}

}  // namespace CommunalCalculator::Core::Test
