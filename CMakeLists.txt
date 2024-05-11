cmake_minimum_required(VERSION 3.5)

project(pic2lines LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# Optional: Enable testing
option(BUILD_TESTS "Build tests" OFF)

# Optionally set BOOST_ROOT from the command line or environment variable
set(BOOST_ROOT "$ENV{BOOST_ROOT}" CACHE PATH "Path to Boost root directory")

# 1.75 for boost.json
# 1.77 boost.json std::string conversion
find_package(Boost 1.77 REQUIRED
  COMPONENTS json
)
include_directories(${Boost_INCLUDE_DIRS})

find_package(spdlog REQUIRED)
find_package(FLTK REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JPEG REQUIRED libjpeg)

set(OBJECT_SRCS
  src/configuration.cpp
  src/configuration.hpp
  src/crossesdrawer.cpp
  src/crossesdrawer.hpp
  src/drawer.cpp
  src/drawer.hpp
  src/drawerfactory.cpp
  src/drawerfactory.hpp
  src/gcodeconfig.cpp
  src/gcodeconfig.hpp
  src/gcodeoutputgenerator.cpp
  src/gcodeoutputgenerator.hpp
  src/gui.cpp
  src/gui.hpp
  src/gui/fltkgui.cpp
  src/gui/fltkgui.hpp
  src/gui/fltkhelpers.cpp
  src/gui/fltkhelpers.hpp
  src/image.cpp
  src/image.hpp
  src/jpeg.cpp
  src/jpeg.hpp
  src/localtypes.hpp
  src/outputconfig.cpp
  src/outputconfig.hpp
  src/outputgenerator.cpp
  src/outputgenerator.hpp
  src/polylinedrawer.cpp
  src/polylinedrawer.hpp
  src/svggenerator.cpp
  src/svggenerator.hpp
  src/textoutputgenerator.cpp
  src/textoutputgenerator.hpp
  src/vec2.hpp
)

# create a lib with the object files (except main)
# so they can be re-used for the tests
add_library(projectObjects OBJECT ${OBJECT_SRCS})

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME}
  projectObjects
  ${JPEG_LIBRARIES}
  Boost::json
  spdlog::spdlog
  ${FLTK_LIBRARIES}
)
target_include_directories(${PROJECT_NAME} PUBLIC ${JPEG_INCLUDE_DIRS} ${FLTK_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${JPEG_CFLAGS_OTHER})


if(BUILD_TESTS)
  add_subdirectory(tests)
endif()

