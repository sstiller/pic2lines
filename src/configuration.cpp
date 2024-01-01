#include "configuration.hpp"

Configuration::~Configuration() = default;

std::string Configuration::toJsonString() const
{
  return json::serialize(toJson());
}

json::value Configuration::toJson() const
{
  return json::object{};
}

void Configuration::fromJson(const json::value& /*input*/)
{
}

void Configuration::fromJsonString(const std::string &jsonString)
{
  fromJson(json::parse(jsonString));
}
