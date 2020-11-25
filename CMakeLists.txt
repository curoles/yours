cmake_minimum_required (VERSION 3.10)

# @copyright Igor Lesik 2015-2020
# @authors   Igor Lesik 2015-2020
# @brief     cmake script to build YOURS.

project(YOURS)
# CMakeLists files in this project can refer to the root source directory
# of the project as ${YOURS_SOURCE_DIR} and to the root binary directory
# of the project as ${YOURS_BINARY_DIR}.

# Requires C++17.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler options.
set(YOURS_M_CFLAGS "-march=native")
set(YOURS_W_CFLAGS "-Werror -Wall -Wextra")
set(YOURS_O_CFLAGS "-O3 -flto")
set(YOURS_COMMON_C_FLAGS "${YOURS_M_CFLAGS} ${YOURS_W_CFLAGS} ${YOURS_O_FLAG}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${YOURS_COMMON_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${YOURS_COMMON_C_FLAGS}")

# Install inside the build directory.
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

#include_directories(.)

add_subdirectory(src)

# Log CMake variables.
MESSAGE( STATUS "CMAKE_C_COMPILER:     " ${CMAKE_C_COMPILER} )
MESSAGE( STATUS "CMAKE_CXX_COMPILER:   " ${CMAKE_CXX_COMPILER} )
MESSAGE( STATUS "CMAKE_CXX_FLAGS:      " ${CMAKE_CXX_FLAGS} )
MESSAGE( STATUS "CMAKE_INSTALL_PREFIX: " ${CMAKE_INSTALL_PREFIX} )
