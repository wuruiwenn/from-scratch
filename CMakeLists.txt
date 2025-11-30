cmake_minimum_required(VERSION 3.10)

project(app)

file(GLOB_RECURSE SRC_FILES "source/*.cpp")
add_executable(app ${SRC_FILES})