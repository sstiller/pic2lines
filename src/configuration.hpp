#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <boost/json.hpp>
#include <memory>
namespace json = boost::json;

class Configuration
{
protected:
  explicit Configuration(const std::string& configType);
public:
  virtual ~Configuration();

  Configuration(const Configuration& other);

  [[nodiscard]] const std::string& configType() const;

  [[nodiscard]] std::string toJsonString() const;

  [[nodiscard]] virtual json::value toJson() const;
  virtual void fromJson(const json::value &input);
  void fromJsonString(const std::string& jsonString);

private:
  class Private;
  std::unique_ptr<Private> prv;
};

#endif // CONFIGURATION_HPP
