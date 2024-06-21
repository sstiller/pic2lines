#ifndef OUTPUTCONFIG_HPP
#define OUTPUTCONFIG_HPP

#include "configuration.hpp"

#include <memory>
#include <string>

class OutputConfig : public Configuration
{
protected:
  OutputConfig(const OutputConfig& other);
public:
  explicit OutputConfig(const std::string configType);
  ~OutputConfig();

  [[nodiscard]] std::string& unit();
  [[nodiscard]] const std::string& unit() const;

  [[nodiscard]] double& width();
  [[nodiscard]] const double& width() const;

  [[nodiscard]] double &height();
  [[nodiscard]] const double& height() const;

private:
  class Private;
  std::unique_ptr<Private> prv;

  // Configuration interface
public:
  [[nodiscard]] json::value toJson() const override;
  void fromJson(const json::value &input) override;
};

#endif // OUTPUTCONFIG_HPP
