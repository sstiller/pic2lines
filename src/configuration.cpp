#include "configuration.hpp"

class Configuration::Private
{
public:
  const std::string configType;
  Private(const std::string& configType)
  : configType{configType}
  {
  }
};


Configuration::Configuration(const std::string& configType)
: prv{std::make_unique<Private>(configType)}
{
}

Configuration::Configuration(const Configuration& other)
: prv{std::make_unique<Private>(other.configType())}
{
}


const std::string& Configuration::configType() const
{
  return prv->configType;
}

Configuration::~Configuration() = default;

std::string Configuration::toJsonString() const
{
  return json::serialize(toJson());
}

json::value Configuration::toJson() const
{
  json::object ret{};
  ret["configType"] = configType();

  return json::object{};
}

void Configuration::fromJson(const json::value& input)
{
  if(input.at("configType").as_string() != configType())
  {
    throw std::invalid_argument("Tried to load wrong config type");
  }
}

void Configuration::fromJsonString(const std::string &jsonString)
{
  fromJson(json::parse(jsonString));
}
