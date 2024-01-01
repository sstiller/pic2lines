#include "outputconfig.hpp"

namespace
{
  const std::string unitString{"unit"};
  const std::string widthString{"width"};
  const std::string heightString{"height"};
}

class OutputConfig::Private
{
public:
  std::string unit{"mm"};
  double width{200.0};
  double height{200.0};
};

OutputConfig::OutputConfig()
: prv{std::make_unique<Private>()}
{
}

OutputConfig::OutputConfig(const OutputConfig& other)
: prv{std::make_unique<Private>(*other.prv)}
{
}

OutputConfig::~OutputConfig() = default;


std::string& OutputConfig::unit()
{
  return prv->unit;
}

const std::string &OutputConfig::unit() const
{
  return prv->unit;
}

double& OutputConfig::width()
{
  return prv->width;
}

const double &OutputConfig::width() const
{
  return prv->width;
}

double& OutputConfig::height()
{
  return prv->height;
}

const double &OutputConfig::height() const
{
  return prv->height;
}

json::value OutputConfig::toJson() const
{
  auto ret = Configuration::toJson();
  auto& object = ret.as_object();
  object[unitString] = unit();
  object[widthString] = width();
  object[heightString] = height();

  return ret;
}

void OutputConfig::fromJson(const json::value& input)
{
  Configuration::fromJson(input);

  unit() = input.at(unitString).as_string();
  width() = input.at(widthString).as_double();
  height() = input.at(heightString).as_double();
}
