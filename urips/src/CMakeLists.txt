CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

SET(CMAKE_TOOLCHAIN_FILE "/home/pi/vcpkg/scripts/buildsystems/vcpkg.cmake")
SET(CMAKE_CXX_STANDARD 17)

PROJECT(urips)
ADD_EXECUTABLE(urips main.cxx)

FIND_PACKAGE(uriparser CONFIG REQUIRED)
TARGET_LINK_LIBRARIES(urips PRIVATE uriparser::uriparser)
