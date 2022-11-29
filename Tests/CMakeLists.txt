cmake_minimum_required(VERSION 3.24)

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

project(communal-calculator-tests)

# Dependency -------------------------------------------------------------------

find_package(GTest REQUIRED)

set(
  third_party_libs
  GTest::gtest_main
  GTest::gmock_main
)

# Sources ----------------------------------------------------------------------

set(
  sources
  SourceFiles/core/app_cfg_manager_test.cpp
  SourceFiles/core/app_cfg_manager_test.h
  SourceFiles/core/app_configuration_test.h
  SourceFiles/core/calculator_test.cpp
  SourceFiles/core/calculator_test.h
  SourceFiles/core/communal_counter_test.cpp
  SourceFiles/core/communal_counter_test.h
  SourceFiles/core/model_test.cpp
  SourceFiles/core/model_test.h
  SourceFiles/core/observer_test.cpp
  SourceFiles/core/observer_test.h
  SourceFiles/core/workspace_test.cpp
  SourceFiles/core/workspace_test.h
  SourceFiles/wrappers/cstd_wrapper_test.h
  SourceFiles/wrappers/std_filesystem_wrapper_test.h
  SourceFiles/wrappers/std_of_stream_wrapper_test.h
  SourceFiles/main.cpp
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

# Target -----------------------------------------------------------------------

set(target ${PROJECT_NAME})

add_executable(
  ${target}
  ${sources}
)

target_include_directories(
  ${target}
  PRIVATE
  SourceFiles
)

target_link_libraries(
  ${target}
  PRIVATE
  ${third_party_libs}
)

