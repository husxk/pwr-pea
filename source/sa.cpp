#include "sa.h"
#include <iostream>

#include <cmath>

void
SA::run()
{
  this->path->fill_path();
  int length = this->path->calculate_path();
  this->best_path->copy();
  this->best_path->set_length(length);

  std::unique_ptr<dummy_path> dummy = std::make_unique<dummy_path>(this->path);
  double temp = this->temperature;

  dummy->copy();

  for(int iters = 0; iters < this->iterations; temp *= this->scale, iters++)
  {
    for(int i = 0; i < this->count; i++)
    {
      // rand <1; n>
      const int j = (rand() % (this->get_size() - 2)) + 1;
      int z;

      do
      {
        z = (rand() % (this->get_size() - 2)) + 1;
      }
      while(j == z);

      dummy->swap_elements(j, z);
      const auto dummy_length = dummy->calculate_path();

      if(length > dummy_length)
      {
        length = dummy_length;
        this->path->copy(dummy->get_path(), dummy->get_size());

        if(length < this->best_path->get_length())
        {
           this->best_path->set_length(length);
           this->best_path->copy();
        }

        continue;
      }

      const double p = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
      auto e = std::exp((double) ((dummy_length - length) * (-1)) / (double) temp);

      if(e > p)
      {
        length = dummy_length;
        this->path->copy(dummy->get_path(), dummy->get_size());
        continue;
      }

      dummy->swap_elements(z, j);
    }
  }

  this->path->set_length(length);
}
