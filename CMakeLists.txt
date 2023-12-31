cmake_minimum_required(VERSION 3.21)
project(FMCA CXX)

message(STATUS "
****************************************************************************
*                  ______   __    __    ______    ______                   * 
*                 |   ___| |  \\  /  |  /   ___|  /      \\                  *
*                 |   __   |   \\/   | |   /     |   /\\   |                 *
*                 |   __|  |        | |  |      |  |__|  |                 *
*                 |  |     |  |\\/|  | |  |      |   __   |                 *
*                 |  |     |  |  |  | |   \\___  |  |  |  |                 *
*                 |__|     |__|  |__|  \\______| |__|  |__|                 *
*                                                                          *
****************************************************************************
This is FMCA, the Fast Multiresolution Covariance Analysis package.

Copyright (c) 2022, Michael Multerer
All rights reserved.

This source code is subject to the GNU Affero General Public License v3.0
license and without any warranty, see <https://github.com/muchip/FMCA>
for further information.
")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(Eigen3 REQUIRED)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.18.0")
  find_package(Python 3.10 COMPONENTS Interpreter Development.Module Development.Embed REQUIRED)
else()
  find_package(Python 3.10 COMPONENTS Interpreter Development REQUIRED)
endif()

find_package(pybind11 REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR})
message("${CMAKE_MODULE_PATH}")
message("${EIGEN3_INCLUDE_DIR}")

set (FMCA_PATH ${PROJECT_SOURCE_DIR})
message("${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_FLAGS "-std=c++11 -I${FMCA_PATH}")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fopenmp")
#-DCMAKE_OSX_ARCHITECTURES=x86_64
set( PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

add_subdirectory(tests)
add_subdirectory(py)
enable_testing()

# Installing the library
install(TARGETS ${PROJECT_NAME}
        EXPORT "${PROJECT_NAME}-config"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
        PRIVATE_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")

install(EXPORT "${PROJECT_NAME}-config" DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
install(DIRECTORY "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")

install(DIRECTORY "${CMAKE_SOURCE_DIR}/py/" DESTINATION "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}" FILES_MATCHING PATTERN "*.ipynb")


