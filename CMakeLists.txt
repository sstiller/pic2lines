cmake_minimum_required(VERSION 3.5)

project(pic2lines LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Optional: Enable testing
option(BUILD_TESTS "Build tests" OFF)

# 1.75 needed for boost.json
find_package(Boost 1.75 REQUIRED
  COMPONENTS json
)


find_package(PkgConfig REQUIRED)
pkg_check_modules(JPEG REQUIRED libjpeg)

set(OBJECT_SRCS
  src/configuration.cpp
  src/configuration.hpp
  src/crossesdrawer.cpp
  src/crossesdrawer.hpp
  src/drawer.cpp
  src/drawer.hpp
  src/gcodeconfig.cpp
  src/gcodeconfig.hpp
  src/gcodeoutputgenerator.cpp
  src/gcodeoutputgenerator.hpp
  src/image.cpp
  src/image.hpp
  src/jpeg.cpp
  src/jpeg.hpp
  src/outputconfig.cpp
  src/outputconfig.hpp
  src/outputgenerator.cpp
  src/outputgenerator.hpp
  src/pic2lines.cpp
  src/pic2lines.hpp
  src/polylinedrawer.cpp
  src/polylinedrawer.hpp
  src/svggenerator.cpp
  src/svggenerator.hpp
  src/textfileoutputgenerator.cpp
  src/textfileoutputgenerator.hpp
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
)
target_include_directories(${PROJECT_NAME} PUBLIC ${JPEG_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${JPEG_CFLAGS_OTHER})


if(BUILD_TESTS)
  add_subdirectory(tests)
endif()

