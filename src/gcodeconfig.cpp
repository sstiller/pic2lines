#include "gcodeconfig.hpp"

namespace
{
  const std::string laserOnCommandString{"laserOnCommand"};
  const std::string laserOffCommandString{"laserOffCommand"};
  const std::string maxPowerString{"maxPower"};
  const std::string travelSpeedString{"travelSpeed"};
  const std::string burningSpeedString{"burningSpeed"};
  const std::string numPassesString{"numPasses"};
}

class GCodeConfig::Private
{
public:
  std::string laserOnCommand{"M04"};
  std::string laserOffCommand{"M05"};
  unsigned int maxPower{255};
  double travelSpeed{3000};
  double burningSpeed{1000};
  unsigned int numPasses{1};
};

GCodeConfig::GCodeConfig()
: prv{std::make_unique<Private>()}
{
}

GCodeConfig::GCodeConfig(const GCodeConfig &other)
: prv{std::make_unique<Private>(*other.prv)}
{
}

GCodeConfig::~GCodeConfig() = default;

std::string &GCodeConfig::laserOnCommand()
{
  return prv->laserOnCommand;
}

const std::string &GCodeConfig::laserOnCommand() const
{
  return prv->laserOnCommand;
}

std::string &GCodeConfig::laserOffCommand()
{
  return prv->laserOffCommand;
}

const std::string &GCodeConfig::laserOffCommand() const
{
  return prv->laserOffCommand;
}

unsigned int &GCodeConfig::maxPower()
{
  return prv->maxPower;
}

const unsigned int &GCodeConfig::maxPower() const
{
  return prv->maxPower;
}

double& GCodeConfig::travelSpeed()
{
  return prv->travelSpeed;
}

const double &GCodeConfig::travelSpeed() const
{
  return prv->travelSpeed;
}

double& GCodeConfig::burningSpeed()
{
  return prv->burningSpeed;
}

const double& GCodeConfig::burningSpeed() const
{
  return prv->burningSpeed;
}

unsigned int &GCodeConfig::numPasses()
{
  return prv->numPasses;
}

const unsigned int &GCodeConfig::numPasses() const
{
  return prv->numPasses;
}

json::value GCodeConfig::toJson() const
{
  auto ret = OutputConfig::toJson();
  auto& object = ret.as_object();

  object[laserOnCommandString] = laserOnCommand();
  object[laserOffCommandString] = laserOffCommand();
  object[maxPowerString] = maxPower();
  object[travelSpeedString] = travelSpeed();
  object[burningSpeedString] = burningSpeed();
  object[numPassesString] = numPasses();

  return ret;
}

void GCodeConfig::fromJson(const json::value &input)
{
  OutputConfig::fromJson(input);
  laserOnCommand() = input.at(laserOnCommandString).as_string();
  laserOffCommand() = input.at(laserOffCommandString).as_string();
  //TODO: why can't we use uint64?
  maxPower() = input.at(maxPowerString).as_int64();
  travelSpeed() = input.at(travelSpeedString).as_double();
  burningSpeed() = input.at(burningSpeedString).as_double();
  numPasses() = input.at(numPassesString).as_int64();
}

