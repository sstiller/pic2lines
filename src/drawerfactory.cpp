#include "drawerfactory.hpp"

#include "crossesdrawer.hpp"
#include "polylinedrawer.hpp"

#include <unordered_map>

namespace
{
  const std::unordered_map<std::string, std::function<std::shared_ptr<Drawer>()>> generators =
    {
      {"crosses", [](){return std::make_shared<CrossesDrawer>();}},
      {"polyline", [](){return std::make_shared<PolyLineDrawer>();}}
    };
}


std::shared_ptr<Drawer> DrawerFactory::create(const std::string& drawerType)
{
  return generators.at(drawerType)();
}

std::vector<std::string> DrawerFactory::availableDrawers()
{
  std::vector<std::string> types;
  types.reserve(generators.size());

  std::transform(generators.begin(), generators.end(), std::back_inserter(types),
                 [](const auto& pair) { return pair.first; });
  return types;
}
