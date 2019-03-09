cmake_minimum_required(VERSION 3.1...3.14)

# If CMake is less than 3.12 the policy is set to the current version.
# If Cmake version is 3.12 or higher than then the cmake_minimum_required syntax will be respected.
if (${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(soa_sorter VERSION 0.1 DESCRIPTION "A sorter for structures of arrays." LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Release)

# Build example and include header only library soa_sort.h
add_executable(example src/example.cc src/soa_sort.h)

add_executable(test_particles tests/particles.cc)
target_include_directories(test_particles PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/)
