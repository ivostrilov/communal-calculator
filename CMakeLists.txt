cmake_minimum_required(VERSION 3.24)

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

project(communal-calculator)
 
option(
  COMMUNALCALCULATOR_BUILD_MODEL_TESTS
  "Build communal_calculator model tests"
  OFF
)

# Dependency -------------------------------------------------------------------

find_package(Qt6 COMPONENTS Quick REQUIRED)

set(
  app_third_party_libs
  Qt6::Quick
)

# Qt setup ---------------------------------------------------------------------

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Sources ----------------------------------------------------------------------

set(
  model_lib_include_dirs
  SourceFiles/model
)

set(
  model_lib_src
  SourceFiles/model/core/app_cfg_manager.cpp
  SourceFiles/model/core/app_cfg_manager.h
  SourceFiles/model/core/app_configuration.cpp
  SourceFiles/model/core/app_configuration.h
  SourceFiles/model/core/calculator.cpp
  SourceFiles/model/core/calculator.h
  SourceFiles/model/core/communal_counter.cpp
  SourceFiles/model/core/communal_counter.h
  SourceFiles/model/core/model.cpp
  SourceFiles/model/core/model.h
  SourceFiles/model/core/observer.h
  SourceFiles/model/core/values_history.h
  SourceFiles/model/core/values_history_manager.cpp
  SourceFiles/model/core/values_history_manager.h
  SourceFiles/model/core/workspace.cpp
  SourceFiles/model/core/workspace.h
  SourceFiles/model/wrappers/cstd_wrapper.cpp
  SourceFiles/model/wrappers/cstd_wrapper.h
  SourceFiles/model/wrappers/std_filesystem_wrapper.cpp
  SourceFiles/model/wrappers/std_filesystem_wrapper.h
  SourceFiles/model/wrappers/std_of_stream_wrapper.cpp
  SourceFiles/model/wrappers/std_of_stream_wrapper.h
)

set(
  app_resources
  Resources/icons/icons.qrc
  Resources/qml/qml.qrc
)

set(
  app_include_dirs
  SourceFiles
)

set(
  app_src
  SourceFiles/model_view/model_view.cpp
  SourceFiles/model_view/model_view.h
  SourceFiles/view/guid_application.cpp
  SourceFiles/view/guid_application.h
  SourceFiles/main.cpp
)

source_group(
  TREE
  ${CMAKE_CURRENT_SOURCE_DIR}
  FILES
  ${app_src}
  ${model_lib_src}
)

# Target -----------------------------------------------------------------------

set(model_lib_target communal-calculator-model-lib)
set(app_target ${PROJECT_NAME})

add_library(
  ${model_lib_target}
  ${model_lib_src}
)

target_include_directories(
  ${model_lib_target}
  PUBLIC
  ${model_lib_include_dirs}
)

add_executable(
  ${app_target}
  ${app_resources}
  ${app_src}
)

target_include_directories(
  ${app_target}
  PRIVATE
  ${app_include_dirs}
)

target_link_libraries(
  ${app_target}
  PRIVATE
  ${model_lib_target}
  ${app_third_party_libs}
)

if (APPLE)

  # Fix error:
  # module "QtQuick" plugin "qtquick2plugin" not found
  # in static linked application ---

  get_target_property(QT_TARGET_TYPE Qt6::Core TYPE)
  if(${QT_TARGET_TYPE} STREQUAL "STATIC_LIBRARY")
    find_package(Qt6QmlImportScanner REQUIRED)
    qt6_import_qml_plugins(${CMAKE_PROJECT_NAME})
  endif()

  # ------------

endif()

if (COMMUNALCALCULATOR_BUILD_MODEL_TESTS)
  add_subdirectory(Tests)
  set(model_tests_target communal-calculator-tests)
  target_include_directories(${model_tests_target} PRIVATE ${app_include_dirs})
  target_link_libraries(${model_tests_target} PRIVATE ${model_lib_target})
endif()

