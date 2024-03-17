cmake_minimum_required(VERSION 3.27)
project(CppExploration)

set(CMAKE_CXX_STANDARD 17)

# Include FetchContent module to download Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you want to fetch
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

# Make Google Test available for use
FetchContent_MakeAvailable(googletest)

add_library(something src/something.cpp)

add_executable(something_test tests/something_test.cpp)
#target_link_libraries(something_test gtest_main)
target_link_libraries(something_test something gtest_main)
add_test(NAME something_test COMMAND something_test)
target_include_directories(something_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

enable_testing()


add_executable(vector src/vector.cpp)
add_executable(if src/if.cpp)
add_executable(optional src/optional.cpp)
add_executable(shared-mutex src/shared-mutex.cpp)

