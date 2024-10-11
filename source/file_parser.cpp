#include <stdio.h>
#include <cstring>
#include <cstdlib>

#include "file_parser.h"
#include "common.h"

void
file_parser::get_filename()
{
  printf("File name (max length:" TO_STR(FILENAME_LENGTH) " ): ");
  scanf("%s", filename);
  getchar(); // skip \n
}

void
file_parser::parse_file()
{
  std::ifstream file;
  file.open(filename);

  if(!file.good())
  {
     printf("Bad filename!");
     file.close();
     return;
  }

  int tmp;

  file >> this->size;

  this->input.reserve(this->size * this->size);

  while(file >> tmp)
    input.push_back(tmp);

  file.close();
}

void
file_parser::print_data()
{
  printf("Size: %d\n", this->size);

  for(int i = 0; i < this->size * this->size; i++)
  {
    printf("%d ", this->input[i]);
    if( (i + 1) % this->size == 0)
      printf("\n");
  }
}

void
file_parser::generate_random(int size_)
{
  this->size = size_;
  this->input.reserve(this->size * this->size);

  for(int i = 0; i < this->size * this->size; i++)
    this->input.emplace_back(std::rand() % 1000);

}
