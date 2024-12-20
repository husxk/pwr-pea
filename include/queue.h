#pragma once

#include "common.h"

class queue_data_t
{

public:

  queue_data_t(size_t size_)
  : size(size_)
  {
    this->path = std::make_unique<int[]>(this->size);
  }

  queue_data_t(size_t size_, int* path, size_t len)
  : size(size_)
  {
    this->path = std::make_unique<int[]>(this->size);
//    std::copy_n(path, this->size, this->path.get());
    copy(path, this->size, this->path.get());

    this->length = len;
  }

  queue_data_t(const queue_data_t& other)
  : size(other.size)
  {
    this->path = std::make_unique<int[]>(this->size);
//    std::copy_n(other.path.get(), this->size, this->path.get());
    copy(other.path.get(), this->size, this->path.get());
    this->elements = other.elements;

    this->length = other.length;;
  }

  queue_data_t(queue_data_t&& other)
  : size(other.size)
  {
    this->path.swap(other.path);

    this->length = other.length;
    this->elements = other.elements;
  }

  auto
  last_element()
  {
    return this->path.get()[elements - 1];
  }

  auto
  add_element(int value, int length)
  {
    this->path.get()[this->elements] = value;
    this->elements++;

    this->length += length;
  }

  auto
  get() const
  {
    return this->path.get();
  }

  auto
  get_length() const
  {
    return this->length;
  }

  auto
  get_elements()
  {
    return elements;
  }


private:
  int length = 0;
  int elements = 0;
  const size_t size;
  std::unique_ptr<int[]> path;
};

struct queue_node_t
{
  queue_node_t(queue_data_t&& other)
  : data(std::forward<queue_data_t>(other))
  {
  }

  ~queue_node_t()
  {
    if(next != nullptr)
      delete this->next;
  }

  queue_data_t data;
  queue_node_t* next = nullptr;
};

class queue_t
{
public:

  ~queue_t()
  {
    if(this->node != nullptr)
      delete this->node;
  }

  void
  add(queue_data_t&& data)
  {
    if(this->node == nullptr)
    {
      this->node = new queue_node_t(std::move(data));
      return;
    }

    auto* tmp = node->next;
    this->node->next = new queue_node_t(std::move(data));
    this->node->next->next = tmp;
  }

  void
  pop_front()
  {
    if(this->node == nullptr)
      return;

    auto* tmp = this->node;
    this->node = this->node->next;

    tmp->next = nullptr;
    delete tmp;
  }

  void
  pop(queue_node_t* other)
  {
    auto* cur = this->node;

    if(cur == other)
    {
        this->pop_front();
        return;
    }

    while(cur->next != other)
      cur = cur->next;

    // cur->next == other
    auto* tmp = cur->next;
    cur->next = tmp->next;

    tmp->next = nullptr;
    delete tmp;
  }

  auto*
  next()
  {
    return this->node;
  }

private:

  queue_node_t* node = nullptr;
};
