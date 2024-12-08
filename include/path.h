#pragma once
#include <cstring>

#include "common.h"

class tsp_path
{
public:
  tsp_path(int path_size_)
  : size(path_size_ * path_size_)
  , path_size(path_size_ + 1)
  {
    path = std::make_unique<int[]>(path_size);
  }

  tsp_path()
  {
  }

public:

  void
  set(int size_, const std::vector<int>& data_)
  {
    this->size = size_;
    this->data = std::make_unique<int[]>(data_.size());

    std::memcpy(this->data.get(), data_.data(), data_.size() * sizeof(int));

    this->path_size = this->size + 1;
    this->path = std::make_unique<int[]>(this->path_size);
    this->path_length = std::numeric_limits<int>::max();
  }

  void
  print()
  {
    printf("\nLength of path: %d\n", this->path_length);
    printf("Path: ");

    for(int i = 0; i < this->path_size; i++)
      printf("%d ", this->path.get()[i]);

    printf("\n");
  }

  void fill_path()
  {
    auto path = this->path.get();
    for(int i = 0; i < this->path_size; i++)
      path[i] = i;

    path[this->size] = 0;
  }

  int
  find_len(int i, int j)
  {
    return this->data.get()[i * this->size + j];
  }

  void
  swap_path(std::unique_ptr<int[]> other, int length)
  {
    this->path.swap(other);
    this->path_length = length;
  }

  int
  calculate_path()
  {
    this->path_length = 0;
    const auto* p = this->path.get();

    for(int i = 1; i < this->path_size; i++)
      this->path_length += this->find_len(p[i - 1], p[i]);

    return this->path_length;
  }

  void
  swap_elements(int i, int j)
  {
    auto* p = this->path.get();
    const auto tmp = p[i];
    p[i] = p[j];
    p[j] = tmp;
  }

  void
  copy(int* other, int size)
  {
    ::copy(other, size, this->path.get());
  }

  int
  get_size()
  {
    return this->path_size;
  }

  void
  set_length(int other)
  {
    this->path_length = other;
  }

  const auto
  get_raw_array()
  {
    return path.get();
  }

  int
  get_length()
  {
    return this->path_length;
  }

private:
  std::unique_ptr<int[]> path;

  std::unique_ptr<int[]> data;

  int path_length;

  // size of data
  int size;

  // real size of path count(0-1-2-...-0)
  int path_size;
};


class
dummy_path
{
public:
  dummy_path(std::shared_ptr<tsp_path> path_)
  : path(path_)
  , path_size(path->get_size())
  {
    dummy = std::make_unique<int[]>(path->get_size());
  }

  void
  swap_elements(int i, int j)
  {
    auto* ptr = dummy.get();
    const auto tmp = ptr[i];
    ptr[i] = ptr[j];
    ptr[j] = tmp;
  }

  void
  copy()
  {
    ::copy(this->path->get_raw_array(), this->path_size, this->dummy.get());
  }

  auto
  get_path()
  {
    return this->dummy.get();
  }

  int
  calculate_path()
  {
    this->path_length = 0;
    const auto* p = this->dummy.get();

    for(int i = 1; i < this->path_size; i++)
      this->path_length += this->path->find_len(p[i - 1], p[i]);

    return this->path_length;
  }

  int
  get_size()
  {
    return this->path_size;
  }

private:
  std::shared_ptr<tsp_path> path;
  std::unique_ptr<int[]> dummy;
  int path_length;
  int path_size;
};
