#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <boost/json.hpp>

namespace json = boost::json;

class Configuration
{
public:
  virtual ~Configuration();

  std::string toJsonString() const;

  virtual json::value toJson() const;
  virtual void fromJson(const json::value &input);
  void fromJsonString(const std::string& jsonString);
};

#endif // CONFIGURATION_HPP
