#ifndef OUTPUTCONFIG_HPP
#define OUTPUTCONFIG_HPP

#include "configuration.hpp"

#include <memory>
#include <string>

class OutputConfig : public Configuration
{
public:
  OutputConfig();
  virtual ~OutputConfig();

  std::string& unit();
  const std::string& unit() const;

  double& width();
  const double& width() const;

  double &height();
  const double& height() const;

private:
  class Private;
  std::unique_ptr<Private> prv;

  // Configuration interface
public:
  json::value toJson() const override;
  void fromJson(const json::value &input) override;
};

#endif // OUTPUTCONFIG_HPP
