cmake_minimum_required(VERSION 3.11)
project(JBeamSim)

# 1. Fetch Raylib automatically
include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(raylib)

# 2. Add your source code
# Make sure the filename matches your .cpp exactly!
add_executable(JBeamSim JBeam2D.cpp "Node.h" "Node.cpp")

# 3. Link the libraries
target_link_libraries(JBeamSim raylib)