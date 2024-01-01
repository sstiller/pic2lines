#include "gcodeconfig.hpp" // from src

#include <gtest/gtest.h>

#include <filesystem> // to get the src dir, needed tor some tests
#include <fstream>
#include <iostream> // TODO: remove

// Test fixture for GCodeConfig class
class GCodeConfigTest : public ::testing::Test {
protected:
  GCodeConfig config;

  // Helper function to set up the config object
  void SetUp() override {
  // You may initialize the config object here before each test case
//        config.maxPower() = 100;
//        config.travelSpeed() = 200;
//        config.burningSpeed() = 50;
//        config.numPasses() = 3;
  }
};


// test base class OutputConfig

TEST_F(GCodeConfigTest, TestUnit) {
  config.unit() = "in";
  EXPECT_EQ(config.unit(), "in");
}
// Test getter and setter for laserOnCommand()
TEST_F(GCodeConfigTest, TestLaserOnCommand) {
  // Check the getter and setter for laserOnCommand()
  EXPECT_EQ(config.laserOnCommand(), "M04");

  // Modify the laserOnCommand and check if it changes
  config.laserOnCommand() = "NewLaserOn";
  EXPECT_EQ(config.laserOnCommand(), "NewLaserOn");
}

// Test getter and setter for laserOffCommand()
TEST_F(GCodeConfigTest, TestLaserOffCommand) {
  // Check the getter and setter for laserOffCommand()
  EXPECT_EQ(config.laserOffCommand(), "M05");

  // Modify the laserOffCommand and check if it changes
  config.laserOffCommand() = "NewLaserOff";
  EXPECT_EQ(config.laserOffCommand(), "NewLaserOff");
}

// Test maxPower() method
TEST_F(GCodeConfigTest, TestMaxPower) {
  config.maxPower() = 100;
  EXPECT_EQ(config.maxPower(), 100);
}

// Test travelSpeed() method
TEST_F(GCodeConfigTest, TestTravelSpeed) {
  config.travelSpeed() = 200;
  EXPECT_EQ(config.travelSpeed(), 200);
}

// Test burningSpeed() method
TEST_F(GCodeConfigTest, TestBurningSpeed) {
  config.burningSpeed() = 50;
  EXPECT_EQ(config.burningSpeed(), 50);
}

// Test numPasses() method
TEST_F(GCodeConfigTest, TestNumPasses) {
  config.numPasses() = 3;
  EXPECT_EQ(config.numPasses(), 3);
}

// Test numPasses() method
TEST_F(GCodeConfigTest, TestToJsonString) {
    // Get the content of the file to compare with
  const std::string currentFilePath = __FILE__;
  const std::filesystem::path currentDirectory = std::filesystem::path(currentFilePath).parent_path();

  std::ifstream file(currentDirectory.string() + "/expectedGcodeConfig.json");
  const std::string expectedContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
std::cout << "expected: " << expectedContent << std::endl;

  // Get the result using your function
  const std::string result = config.toJsonString();
std::cout << "result: " << result << std::endl;

  // Compare the result with the content of the file
  EXPECT_EQ(result, expectedContent);
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
