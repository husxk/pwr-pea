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

  void get_filename();
  void parse_file();

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
};