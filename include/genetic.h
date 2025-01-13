#pragma once

#include "vector.hpp"
#include "common.h"


class Genetic
{
  struct pop
  {
    pop()
    {
      this->dummy_size = 0;
    }

    pop(pop&& other)
    {
      this->dummy.swap(other.dummy);
      this->dummy_size = other.dummy_size;
    }

    pop(const pop& other)
    {
      this->dummy = other.dummy;
      this->dummy_size = other.dummy_size;
    }


    pop(std::shared_ptr<dummy_path> d)
    {
      this->dummy = d;
      this->dummy_size = this->dummy->calculate_path();
    }

    pop& operator=(pop&& other)
    {
      this->dummy.swap(other.dummy);
      this->dummy_size = other.dummy_size;

      return *this;
    }

    void print()
    {
      printf("Size: %d ", dummy_size);
      dummy->print();
    }

    int size()
    {
      return this->dummy_size;
    }

    std::shared_ptr<dummy_path> dummy;
    int dummy_size;
  };

public:

  void
  run()
  {
    create_population();

    for (int i = 0; i < this->iterations; i++)
    {
      this->selection();
      this->mutation();

      this->sort();
      this->population_clean_up();

/*      printf("\n%d Iteration:\n", i);
      this->population.print();
      printf("\n^^^^^^^^^^^^^^^^^\n");
*/
    }

      this->population.print();
  }

  void
  set(int n, const std::vector<int>& data)
  {
    path = std::make_shared<tsp_path>(n);
    this->path->set(n, data);

    // reserve more in advance
    this->population.reserve(2 * population_count);
  }


private:

  void
  selection()
  {
    // there is nothing really to do,
    // as we will always take upper half of
    // sorted population for mutation

    this->index = (this->population_count / 2);

    return;
  }

  int
  rand_next(int i)
  {
    int ret = 0;

    do
    {
      ret = rand() % this->index;
    } while(ret == i);

    return ret;
  }

  void
  population_clean_up()
  {
    for(int i = this->population.get_elements(); i >= this->population_count; i--)
      this->population.pop();

  }

  void
  mutation()
  {
    mutation_half_half();
  }

  void
  mutation_half_half()
  {int i;
    for(i = 0; i < this->population_count; i++)
      mutation_half_half_();
//    printf("\nCalled: %d\n", i);
  }

  void
  mutation_half_half_()
  {
    const int first = rand() % this->index;
    const int second = rand_next(first);

    std::shared_ptr<dummy_path> dummy = std::make_shared<dummy_path>(this->path);

    int* arr = dummy->get_path();
    const int size = dummy->get_size() - 1;

    int* first_ptr  = this->population.get_array()[first].dummy->get_path();
    int* second_ptr = this->population.get_array()[second].dummy->get_path();

    const int taken_from_first = size / 2;

    // copy first half
    ::copy(first_ptr, taken_from_first, arr);

    for(int i = taken_from_first, z = 0; i < size; i++)
    {
      bool emplaced = false;

      do
      {
        bool found = false;

        const int city = second_ptr[z];

        for(int j = 1; j < size; j++)
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

    this->population.add(std::move(dummy));
  }

  void
  create_population()
  {
    for(int i = 0; i < this->population_count; i++)
    {
      std::shared_ptr<dummy_path> dummy = std::make_shared<dummy_path>(this->path);
      dummy->generate_random_path();

      this->population.add(pop(std::move(dummy)));
    }

    this->sort();
  }

  void
  sort()
  {
    auto shared_array = this->population.get_array();
    this->quicksort(shared_array.get(), 0, this->population.get_elements() - 1);
  }

  int
  partition(pop arr[], int low, int high)
  {
    const int pivot = arr[high].size();
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j].size() < pivot)
        {
            i++;
            this->swap(i, j);
        }
    }

    this->swap(i + 1, high);

    return i + 1;
  }

  void
  quicksort(pop arr[], int low, int high)
  {
    if (low < high) {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
  }

  void
  swap(int i, int j)
  {
    auto shared_array = this->population.get_array();
    auto arr = shared_array.get();

    pop tmp = std::move(arr[i]);
    arr[i] = std::move(arr[j]);
    arr[j] = std::move(tmp);

  }

  private:

  int iterations = 100;
  int population_count = 500;

  // selection should set this as index to which we can perform mutation
  int index = 0;

  Vector<pop> population;
  std::shared_ptr<tsp_path> path;

};
