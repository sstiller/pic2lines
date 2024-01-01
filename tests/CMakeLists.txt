# Set up the test project
project(MyProjectTests)

# Locate and include Google Test
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/src)

# Get all test source files that start with 'test_' in the current directory
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test_*.cpp)

# Add an executable for each test source file
foreach(TEST_SRC ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)

    add_executable(${TEST_NAME} ${TEST_SRC})

    # Include the object files generated from 'src' directory
    target_sources(${TEST_NAME} PRIVATE $<TARGET_OBJECTS:projectObjects>)

    # Link against Google Test or any other testing framework
    target_link_libraries(${TEST_NAME}
      gtest
      GTest::gmock
      GTest::gtest_main
      Boost::json
      ${JPEG_LIBRARIES}
    ) # Link against Google Test

    # Specify the directories to search for header files
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src) # Include directories for project files

    # Optionally, set additional properties for the test executables
    set_target_properties(${TEST_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
    )

    # Optionally, enable testing
    enable_testing()

    # Add each test executable as a 'make test' target
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
