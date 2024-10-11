#include "graph.h"

#include <limits>
#include <cstdio>

void
graph::set(int size_, std::vector<int> data_)
{
  this->size = size_;
  this->data = std::make_unique<int[]>(data_.size());

  std::memcpy(this->data.get(), data_.data(), data_.size() * sizeof(int));

  this->path_size = this->size + 1;
  this->shortest_path = std::make_unique<int[]>(this->path_size);
  this->path_length = std::numeric_limits<int>::max();
}

void
graph::print()
{
  printf("\nLength of path: %d\n", this->path_length);
  printf("Path: ");

  for(int i = 0; i < this->path_size; i++)
    printf("%d ", this->shortest_path.get()[i]);

  printf("\n");
}

bool
graph::get_next_permutation(int* permutation)
{
  return std::next_permutation(permutation + 1, permutation + this->size);
}

void
graph::fill_path(int* path)
{
  for(int i = 0; i < this->size; i++)
    path[i] = i;

  path[this->size] = 0;
}

int
graph::find_len(int i, int j)
{
  return this->data.get()[i * this->size + j];
}

void
graph::brute_force()
{
  auto path = std::make_unique<int[]>(this->path_size);
  this->fill_path(path.get());

  int current_length = 0;

  do
  {
    for(int i = 1; i < this->path_size; i++)
      current_length += this->find_len(path[i - 1], path[i]);

    if(this->path_length > current_length)
    {
      this->path_length = current_length;
      std::memcpy(this->shortest_path.get(), path.get(), this->size * sizeof(int));
    }

    current_length = 0;
  } while(this->get_next_permutation(path.get()));

}
