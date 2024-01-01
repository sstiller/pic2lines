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
  unsigned int width{200};
  unsigned int height{200};
};

OutputConfig::OutputConfig()
: prv{std::make_unique<Private>()}
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

unsigned int& OutputConfig::width()
{
  return prv->width;
}

const unsigned int& OutputConfig::width() const
{
  return prv->width;
}

unsigned int& OutputConfig::height()
{
  return prv->height;
}

const unsigned int& OutputConfig::height() const
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
  auto& object = input.as_object();
  unit() = input.at(unitString).as_string();

  // TODO: why can't we use uint64?
  width() = input.at(widthString).as_int64();

  height() = input.at(heightString).as_int64();
}
