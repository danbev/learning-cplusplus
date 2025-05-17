cmake_minimum_required(VERSION 3.10)
project(SDLAudioCapture)

set(CMAKE_CXX_STANDARD 17)

# Find SDL2
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

# Add executable
add_executable(audio_capture src/audio_capture.cpp)

# Link SDL2
target_link_libraries(audio_capture ${SDL2_LIBRARIES})
target_include_directories(audio_capture PRIVATE ${SDL2_INCLUDE_DIRS})
target_compile_options(audio_capture PRIVATE ${SDL2_CFLAGS_OTHER})

# Alternative if you have SDL2 installed via vcpkg or find_package works
# find_package(SDL2 REQUIRED)
# target_link_libraries(audio_capture SDL2::SDL2 SDL2::SDL2main)
