#include "gcodeconfig.hpp"

class GCodeConfig::Private
{
public:
  std::string laserOnCommand{"M04"};
  std::string laserOffCommand{"M05"};
  unsigned int maxPower{255};
  unsigned int travelSpeed{3000};
  unsigned int burningSpeed{1000};
  unsigned int numPasses{1};
};

GCodeConfig::GCodeConfig()
{

}
