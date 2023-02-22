cmake_minimum_required(VERSION 3.15)

project(polymorphic_logger_example CXX)

add_executable(polymorphic_logger_example
  src/main.cpp
  src/logger.hpp
  src/logger_file.hpp
  src/logger_file.cpp
  src/logger_udp.hpp
  src/logger_udp.cpp
  src/logger_aggregator.hpp
  src/logger_aggregator.cpp)

target_compile_features(polymorphic_logger_example
  PUBLIC cxx_std_17)
set_target_properties(polymorphic_logger_example
  PROPERTIES CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.70 REQUIRED)
add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(polymorphic_logger_example ${Boost_LIBRARY_DIRS})

set(CMAKE_CXX_CLANG_TIDY polymorphic_logger_example -warnings-as-errors=*)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
  CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(polymorphic_logger_example
    PRIVATE -g -Wall -Wextra -Werror -pedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(polymorphic_logger_example
    PRIVATE /EHsc /W4 /WX)
endif()