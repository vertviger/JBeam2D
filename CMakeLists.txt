cmake_minimum_required(VERSION 3.11)
project(JBeamSim)

include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(raylib)

add_executable(JBeamSim JBeam2D.cpp "Node.h" "Node.cpp" "Beam.h" "Beam.cpp")

target_link_libraries(JBeamSim raylib)