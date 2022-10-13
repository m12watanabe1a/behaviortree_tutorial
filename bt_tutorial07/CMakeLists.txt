cmake_minimum_required(VERSION 3.8)
project(bt_tutorial07)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

find_package(behaviortree_cpp_v3 3.7 QUIET)
if(PACKAGES_FOUND)
  # ===================================================================
  ament_auto_add_executable(my_tree src/main.cpp)
  # ===================================================================
endif()
if(NOT PACKAGES_FOUND)
  message(STATUS "behaviortree_cpp_v3 3.7 required for this tutorial.")
endif()

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_auto_package(
  INSTALL_TO_SHARE
    trees)
