cmake_minimum_required (VERSION 3.16.3)
project(Demo CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pg -Wall")
# Commentaire
add_executable(exe trace.cxx Vec3.h)
