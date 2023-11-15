cmake_minimum_required(VERSION 3.5)

project(pic2lines LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JPEG REQUIRED libjpeg)

set(SOURCES
  src/crossesdrawer.cpp
  src/crossesdrawer.h
  src/drawer.cpp
  src/drawer.h
  src/gcodeoutputgenerator.cpp
  src/gcodeoutputgenerator.h
  src/image.cpp
  src/image.h
  src/jpeg.cpp
  src/jpeg.h
  src/main.cpp
  src/outputgenerator.cpp
  src/outputgenerator.h
  src/pic2lines.cpp
  src/pic2lines.h
  src/polylinedrawer.cpp
  src/polylinedrawer.h
  src/svggenerator.cpp
  src/svggenerator.h
  src/textfileoutputgenerator.cpp
  src/textfileoutputgenerator.h
  src/vec2.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${JPEG_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${JPEG_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${JPEG_CFLAGS_OTHER})



