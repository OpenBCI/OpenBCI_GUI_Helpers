cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(openbci-gui-helpers LANGUAGES CXX)
SET(VERSION "3.0.0" CACHE STRING "Version")

include(cmake/default.cmake)
include(modules/bglib/build.cmake)
include(modules/native-ble/build.cmake)

add_subdirectory(3rdparty/SimpleBLE/simpleble)