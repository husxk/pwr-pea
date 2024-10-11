#pragma once

#include <vector>
#include <memory>
#include <cstring>

class graph
{
 public:
  graph()
  {
  }

  void
  set(int, std::vector<int>);

  void
  brute_force();

  void
  print();

private:
  int size;
  int path_size;

  std::unique_ptr<int[]> data;

  std::unique_ptr<int[]> shortest_path;
  int path_length;


private:
  bool
  get_next_permutation(int*);

  void
  fill_path(int*);

  int
  find_len(int, int);

};
