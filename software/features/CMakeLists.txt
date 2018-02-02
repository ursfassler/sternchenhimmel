cmake_minimum_required(VERSION 3.7)

project(sternchenhimmel-features)

file(GLOB SOURCES
  "step_definitions/*.h"
  "step_definitions/*.cpp"
  "*.feature"
  "../logic/*.h"
  "../logic/*.cpp"
)

include_directories(../logic/)

add_executable(sternchenhimmel-features ${SOURCES})
target_link_libraries(sternchenhimmel-features cucumber-cpp)
target_link_libraries(sternchenhimmel-features boost_filesystem boost_system boost_regex boost_program_options)
target_link_libraries(sternchenhimmel-features gmock gtest pthread)

set_property(TARGET sternchenhimmel-features PROPERTY CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
