#include "configuration.hpp"
#include <iostream> // TODO: remove
Configuration::~Configuration() = default;

std::string Configuration::toJsonString() const
{
  return json::serialize(toJson());
}

json::value Configuration::toJson() const
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  return json::object{};
}

void Configuration::fromJson(const json::value& /*input*/)
{
}

void Configuration::fromJson(const std::string &jsonString)
{
  fromJson(json::parse(jsonString));
}
