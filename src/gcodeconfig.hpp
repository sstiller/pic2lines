#ifndef GCODECONFIG_H
#define GCODECONFIG_H

#include <string>
#include <memory>

class GCodeConfig
{
public:
  GCodeConfig();

  std::string& laserOnCommand();
  const std::string& laserOnCommand() const;

  std::string& laserOffCommand();
  const std::string& laserOffCommand() const;

  unsigned int& maxPower();
  const unsigned int& maxPower() const;

  unsigned int& travelSpeed();
  const unsigned int& travelSpeed() const;

  unsigned int& burningSpeed();
  const unsigned int& burningSpeed() const;

  unsigned int& numPasses();
  const unsigned int& numPasses() const;

private:
  class Private;
  std::unique_ptr<Private> prv;
};

#endif // GCODECONFIG_H
