#pragma once

#include <vector>
#include <memory>
#include <cstring>
#include <limits>

#include "queue.h"
#include "sa.h"
#include "genetic.h"

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
  set_genetic_params(double x, double y)
  {
    this->genetic->set_params(x, y);
  }

  void
  set_genetic_tournament(int s)
  {
    this->genetic->set_tournament(s);
  }

  void
  set_genetic_iters(int s)
  {
    this->genetic->set_iters(s);
  }


 
  void
  brute_force();

  void
  bb();

  void
  run_sa();

  void
  run_genetic();

  void
  print();

  void
  permutate(int*, int);

  void
  find_mins(int*);

  void
  set_sa(int, int, double);

  void
  set_pop(int pop)
  {
    this->genetic->set_pop(pop);
  }

  void
  print_best_sa();

  auto
  get_result()
  {
    return this->path_length;
  }

private:
  int size;
  int path_size;

  std::unique_ptr<int[]> data;

  std::unique_ptr<int[]> shortest_path;
  int path_length = std::numeric_limits<int>::max();

  std::unique_ptr<queue_t> queue = std::make_unique<queue_t>();

  std::shared_ptr<SA> sa;
  int sa_temperature = SA::DEFAULT_TEMP;
  int sa_iterations = SA::DEFAULT_ITERATIONS;
  double sa_scale = SA::DEFAULT_SCALE;

  std::unique_ptr<Genetic> genetic;

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
