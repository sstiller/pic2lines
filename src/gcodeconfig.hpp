#ifndef GCODECONFIG_HPP
#define GCODECONFIG_HPP

#include "outputconfig.hpp"

#include <string>
#include <memory>

class GCodeConfig final : public OutputConfig
{
public:
  GCodeConfig();

  GCodeConfig(const GCodeConfig& other);

  ~GCodeConfig();

  [[nodiscard]] std::string& laserOnCommand();
  [[nodiscard]] const std::string& laserOnCommand() const;

  [[nodiscard]] std::string& laserOffCommand();
  [[nodiscard]] const std::string& laserOffCommand() const;

  [[nodiscard]] unsigned int& maxPower();
  [[nodiscard]] const unsigned int& maxPower() const;

  // units / min
  [[nodiscard]] double& travelSpeed();
  [[nodiscard]] const double& travelSpeed() const;

  // units / min
  [[nodiscard]] double& burningSpeed();
  [[nodiscard]] const double& burningSpeed() const;

  [[nodiscard]] unsigned int& numPasses();
  [[nodiscard]] const unsigned int& numPasses() const;

private:
  class Private;
  std::unique_ptr<Private> prv;

  // Configuration interface
public:
  [[nodiscard]] json::value toJson() const;
  void fromJson(const json::value &input);
};

#endif // GCODECONFIG_HPP
