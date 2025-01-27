#pragma once

#include <vector>
#include <limits>

#include "vector.hpp"
#include "common.h"


class Genetic
{
public:

  void
  set_pop(int pop)
  {
    this->population_count = pop;
  }

  void
  set_params(double mut, double cross)
  {
    MUTATION_RATE = mut;
    CROSS_RATE = cross;
  }
  void

  set_tournament(int size)
  {
    tournament_size = size;
  }

  void
  set_iters(int i)
  {
    this->iterations = i;
  }


  void
  run()
  {
    run_genetic();
  }

  void
  set(int n, const std::vector<int>& data)
  {
    path = std::make_shared<tsp_path>(n);
    this->path->set(n, data);

    // reserve more in advance
    this->population.reserve(2 * population_count);
  }

  auto
  get_best_array()
  {
    return this->best_path->get_path();
  }

  auto
  get_length_best()
  {
    return this->best_path->get_length();
  }

  void
  calc()
  {
    this->best_path->calculate_path();
  }


private:

  void
  create_population()
  {
    for(unsigned int i = 0; i < this->population_count; i++)
    {
      dummy_path dummy(this->path);

      dummy.generate_random_path();

      this->population.push_back(std::move(dummy));
    }

    this->best_path = std::make_unique<dummy_path>(this->population[0]);
  }

  dummy_path
  tournament()
  {
    dummy_path* best = &this->population[rand() % this->population_count];

    for (int i = 0; i < this->tournament_size; i++)
    {
        dummy_path* p = &this->population[rand() % this->population_count];

        if(p == best)
        {
           --i;
           continue;
        }

        if (p->get_length() < best->get_length())
        {
            best = p;
        }
    }

    dummy_path tmp(*best);

    best->set_length(std::numeric_limits<int>::max());

    return tmp;
  }

  dummy_path
  cross(dummy_path* parent1, dummy_path* parent2)
  {
    // create child
    dummy_path dummy(*parent1);

    int* arr = dummy.get_path();
    const int size = dummy.get_size() - 1;

    const int* second_ptr = parent2->get_path();

    const int taken_from_first = size / 2;

    // dummy is deep copy of parent1, so we need to override
    // second half of dummy

    for(int i = taken_from_first, z = 1; i < size; i++)
    {
      bool emplaced = false;

      do
      {
        bool found = false;

        const int city = second_ptr[z];

        for(int j = 1; j < i; j++)
        {
            if(arr[j] == city)
            {
              found = true;
              break;
            }
        }

        if(!found)
        {
            emplaced = true;
            arr[i] = city;
        }

        z++;

      } while(!emplaced);
    }

    return dummy;
  }

  void
  mutate(dummy_path& p)
  {
      int i;
      for(i = 0; i == 0; i = rand() % (p.get_size() - 1));

      int j;
      for(j = i; j == i || j == 0; j = rand() % (p.get_size() - 1));

      p.swap_elements(i, j);
      p.calculate_path();
  }

  void
  setup()
  {
    this->population.clear();
  }

  void
  run_genetic()
  {
    this->setup();
    this->create_population();

    for (int i = 0; i < this->iterations; i++)
    {
        std::vector<dummy_path> new_population;
        new_population.reserve(this->population_count);

        // recreate  population
        while (true)
        {
            dummy_path p1 = tournament();
            dummy_path p2 = tournament();

            // add child
            if (((double) rand() / RAND_MAX) < CROSS_RATE)
            {
              if(new_population.size() == this->population_count)
                break;

              dummy_path p3 = cross(&p1, &p2);

              if ((double)rand() / RAND_MAX < MUTATION_RATE)
                  mutate(p3);

              p3.calculate_path();
              new_population.push_back(p3);
            }

            // add p1
            if(new_population.size() ==  this->population_count)
              break;

            if ((double)rand() / RAND_MAX < MUTATION_RATE)
              mutate(p1);

            new_population.push_back(p1);

            // add p2
            if(new_population.size() ==  this->population_count)
              break;

            if ((double)rand() / RAND_MAX < MUTATION_RATE)
              mutate(p2);

            new_population.push_back(p2);
        }

        population.swap(new_population);
        find_best();
    }
  }

  void
  find_best()
  {
    for(unsigned int i = 0; i < this->population.size(); i++)
    {
      if(population[i].get_length() < best_path->get_length())
      {
        this->best_path = std::make_unique<dummy_path>(this->population[i]);
      }
    }
  }

private:

  int iterations = 1000;
  unsigned int population_count = 500;
  int tournament_size = 5;
  double pop_percentage = 0.8;

  double MUTATION_RATE = 0.2;
  double CROSS_RATE = 0.8;

  std::vector<dummy_path> population;
  std::shared_ptr<tsp_path> path;
  std::unique_ptr<dummy_path> best_path;

};
