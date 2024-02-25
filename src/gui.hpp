#ifndef GUI_HPP
#define GUI_HPP

#include "localtypes.hpp"

#include <memory>
#include <string>
#include <vector>

/**
 * @brief The Gui class is a base for a GUI implementation.
 * It keeps all the configurations and processes GUI events.
 * It provides protected functions for use by the GUI implementation
 * and maybe some signals to communicate with the outside world.
 */
class Gui
{
public:
  Gui();
  virtual ~Gui();

  /**
   * @brief startEventLoop runsthe GUI framework specific event loop.
   * This function can be called from any thread.
   * It must quit when \ref stopEventLoop is called.
   * If this function returns, the main program may quit or restart it (not decided yet).
   */
  virtual void runEventLoop(int argc, char** argv) = 0;

  /**
   * @brief stopEventLoop stops the event loop, if running.
   */
  virtual void stopEventLoop() = 0;

protected:
  virtual void displayErrorMessage(const std::string& message) = 0;
  /**
   * @brief availableDrawers returns the available drawer implementations.
   * One of the returned drawers can be used in @ref generateOutput
   * @return the names of the available drawers.
   */
  static std::vector<std::string> availableDrawers();

  /**
   * @brief getPreviewOutputGenerator returns the OutputGenerator, used to create a preview image for the GUI.
   * @return the preview OutputGenerator if existing. Otherwise empty pointer.
   */
  virtual std::shared_ptr<OutputGenerator> getPreviewOutputGenerator();

  /**
   * @brief generatePreview draws a preview image using @ref getPreviewDrawer.
   * If there is no preview drawer, nothing happens.
   * @param inputImage
   */
  void generatePreview(std::shared_ptr<const Image> inputImage);

  /**
   * @brief available OutputGenerators returns the available OutputGenerator implementations.
   * @return the names of the available OutputGenerators.
   */
  static std::vector<std::string> availableOutputGenerators();

  /**
   * @brief generateOutput creates the output file using the input image and the given drawer
   * @param drawerName
   * @param fileName
   * @todo make generator configurable, too
   */
  void generateOutput(const std::string& outFilePath);

  /**
   * @brief readInputJpeg reads a jpeg file and creates an Image
   * @param path file nale of the jpeg file
   * @return the decoded image
   */
  static std::shared_ptr<Image> readInputJpeg(const std::string& path);

protected:
  std::string selectedInputImagePath;
  std::string selectedDrawer;
  std::string selectedOutputGenerator;
};

#endif // GUI_HPP
