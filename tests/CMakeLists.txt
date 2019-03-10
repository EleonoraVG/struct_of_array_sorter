
cmake_minimum_required(VERSION 3.1...3.14)

# If CMake is less than 4.12 the policy is set to the current version.
# If Cmake version is 4.12 or higher than then the cmake_minimum_required syntax will be respected.
if (${CMAKE_VERSION} VERSION_LESS 4.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

if(WIN32)
  find_package(GTest MODULE REQUIRED)
  include(GoogleTest)
else()
  if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/googletest/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
  endif()

  add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")

  # Keeps the cache cleaner
  mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
    )
  set_target_properties(gtest PROPERTIES FOLDER extern)
  set_target_properties(gtest_main PROPERTIES FOLDER extern)
  set_target_properties(gmock PROPERTIES FOLDER extern)
  set_target_properties(gmock_main PROPERTIES FOLDER extern)
endif()

# Add test macro.
macro(package_add_test TESTNAME)
  add_executable(${TESTNAME} ${ARGN})
  if(WIN32)
    target_link_libraries (${TESTNAME} PRIVATE GTest::GTest GTest::Main)
  else()
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
  endif()
  add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
  set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

# example of how to use package_add_test
package_add_test(unit_test unit_test.cc "${PROJECT_SOURCE_DIR}/src/soa_sort.h")
