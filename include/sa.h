#pragma once
#include <vector>
#include <memory>

#include "path.h"

class SA
{
public:
  static constexpr double DEFAULT_TEMP = 10000;
  static constexpr int DEFAULT_ITERATIONS = 10000;
  static constexpr double DEFAULT_SCALE = 0.999;
public:

  SA(int n, const std::vector<int>& data, double temp = DEFAULT_TEMP, double scl = DEFAULT_SCALE, int iters = DEFAULT_ITERATIONS)
  : temperature(temp)
  , scale(scl)
  , count(n * n)
  , iterations(iters)
  {
    path = std::make_shared<tsp_path>(n);
    this->path->set(n, data);
  }

public:

  void
  run();

  int
  get_size()
  {
    return this->path->get_size();
  }

  const auto
  get_raw_array()
  {
    return path.get()->get_raw_array();
  }

  int
  get_length()
  {
    return this->path->get_length();
  }

  void
  set(int temperature, int iterations, double scale)
  {
    this->temperature = temperature;
    this->iterations = iterations;
    this->scale = scale;
  }

private:

private:
  double temperature = 0.0;
  double scale = 0.0;
  int count = 0;

  std::shared_ptr<tsp_path> path;
  int cost = 0;
  int iterations = 0;
};
