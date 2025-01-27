#pragma once
#include <fstream>
#include <vector>

#include "graph.h"

#define FILENAME_LENGTH 1024

static constexpr size_t
READ_BUFFER_SIZE = 2048;

class file_parser
{
  char filename [FILENAME_LENGTH];
  int size;
  std::vector<int> input;

public:

  file_parser()
  {
  }

  void
  get_filename();

  void
  set_filename(const char* file, int length)
  {
    memcpy(filename, file, length);
  }

  void
  parse_file();

  void
  generate_random(int);

  void print_data();

  void
  clear()
  {
    this->size = 0;
    input.clear();
  }

  std::vector<int>
  get_input()
  {
    return this->input;
  }

  int
  get_size()
  {
    return this->size;
  }
};
