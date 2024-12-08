#pragma once

#include <vector>
#include <memory>
#include <cstring>
#include <limits>

#include "queue.h"
#include "sa.h"

class graph
{
 public:
  graph()
  {
  }

  void
  clear();

  void
  set(int, std::vector<int>);

  void
  brute_force();

  void
  bb();

  void
  run_sa();

  void
  print();

  void
  permutate(int*, int);

  void
  find_mins(int*);

private:
  int size;
  int path_size;

  std::unique_ptr<int[]> data;

  std::unique_ptr<int[]> shortest_path;
  int path_length = std::numeric_limits<int>::max();

  std::unique_ptr<queue_t> queue = std::make_unique<queue_t>();

  std::unique_ptr<SA> sa;

private:
  bool
  get_next_permutation(int*);

  void
  fill_path(int*);

  int
  find_len(int, int);

  int
  add_mins(bool*, int*);

  void
  change_shortest_path(int*, int);

  void
  bb_calculate_path(queue_data_t&, int*);

  void
  bb_work_loop(int*);

  void
  bb_recheck_queue();
};
