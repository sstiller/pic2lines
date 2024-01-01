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

  std::string& laserOnCommand();
  const std::string& laserOnCommand() const;

  std::string& laserOffCommand();
  const std::string& laserOffCommand() const;

  unsigned int& maxPower();
  const unsigned int& maxPower() const;

  // units / min
  double& travelSpeed();
  const double& travelSpeed() const;

  // units / min
  double& burningSpeed();
  const double& burningSpeed() const;

  unsigned int& numPasses();
  const unsigned int& numPasses() const;

private:
  class Private;
  std::unique_ptr<Private> prv;

  // Configuration interface
public:
  json::value toJson() const;
  void fromJson(const json::value &input);
};

#endif // GCODECONFIG_HPP
