#ifndef DRAWERFACTORY_HPP
#define DRAWERFACTORY_HPP

#include "drawer.hpp"

#include <string>
#include <vector>

class DrawerFactory
{
public:
  static std::shared_ptr<Drawer> create(const std::string& drawerType);
  static std::vector<std::string> availableDrawers();
};

#endif // DRAWERFACTORY_HPP
