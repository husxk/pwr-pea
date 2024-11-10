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

  this->path_length = std::numeric_limits<int>::max();
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

void
graph::find_mins(int* arr)
{
  for(int i = 0; i < this->size; i++)
  {
    int min = std::numeric_limits<int>::max();
    for(int j = 0; j < this->size; j++)
    {
      if(i == j)
        continue;

      const int current = this->data.get()[i * this->size + j];

      if(min > current)
        min = current;
    }

    arr[i] = min;
  }
}

int
graph::add_mins(bool* visited, int* mins)
{
  int length = 0;

  for(int i = 0; i < this->size; i++)
    if(visited[i] == false)
      length += mins[i];

  return length;
}

void
graph::bb_calculate_path(queue_data_t& path, int* mins)
{
  // set visited
  std::unique_ptr visited = std::make_unique<bool[]>(this->size);
  std::memset(visited.get(), 0, sizeof(bool) * this->size);

  for(int i = 0; i < path.get_elements(); i++)
    visited[path.get()[i]] = true;

  const int last = path.last_element();

  for(int i = 0; i < this->size; i++)
  {
    if(visited[i] == true)
      continue;

    int length = path.get_length();

    const int cost = this->find_len(last, i);
    length += cost;

    visited.get()[i] = true;
    length += this->add_mins(visited.get(), mins);
    visited.get()[i] = false;

    if(length >= this->path_length)
      continue;

    // current length (valid or with mins)
    // is less than best found yet
    // either add to queue (res with mins)
    // or add as a new best and recheck
    // the queue for any lengths that are larger
    // that that

    // path is 'full' with node at i
    // we need to manually add last node (back to the first)
    // and recheck for needed length
    if(path.get_elements() == this->path_size - 2)
    {
      length += this->find_len(i, 0);

      if(length >= this->path_length)
        continue;

      queue_data_t data(path);
      data.add_element(i, cost);
      data.add_element(0, this->find_len(i, 0));

      this->change_shortest_path(data.get(), length);
      this->bb_recheck_queue();

      continue;
    }

    queue_data_t data(path);
    data.add_element(i, cost);
    this->queue.get()->add(std::move(data));
  }
}

void
graph::change_shortest_path(int* path, int length)
{
  std::copy_n(path, this->path_size, this->shortest_path.get());
  this->path_length = length;
}

void
graph::bb_recheck_queue()
{
  // we need to skip front entry as we are currently checking it
  auto* cur = this->queue.get()->next();
  if(cur == nullptr)
    return;

  cur = cur->next;

  while(cur != nullptr)
  {
    if(cur->data.get_length() >= this->path_length)
    {
      if(cur->next == nullptr)
      {
          this->queue.get()->pop(cur);
          break;
      }

      auto* tmp = cur->next;
      this->queue.get()->pop(cur);
      cur = tmp;
      continue;
    }

    cur = cur->next;
  }
}

void
graph::bb_work_loop(int* mins)
{
  while(this->queue.get()->next() != nullptr)
  {
    auto* data = this->queue.get()->next();
    this->bb_calculate_path(data->data, mins);
    this->queue.get()->pop_front();
  }
}

void
graph::bb()
{
  std::unique_ptr mins = std::make_unique<int[]>(this->size);
  this->find_mins(mins.get());

  queue_data_t data(this->path_size);
  data.add_element(0, 0);
  this->queue.get()->add(std::move(data));

  // guess that best path is 'first' path
  auto path = std::make_unique<int[]>(this->path_size);
  this->fill_path(path.get());

  this->path_length = 0;
  for(int i = 1; i < this->path_size; i++)
    this->path_length += this->find_len(path.get()[i - 1], path.get()[i]);

  this->change_shortest_path(path.get(), this->path_length);

  this->bb_work_loop(mins.get());
}
