#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "file_parser.h"
#include "graph.h"

static int
menu()
{
  printf("\nChoose:\n");
  printf("1. Load data from file\n");
  printf("2. Generate data\n");
  printf("3. Show data\n");
  printf("8. Exit\n");
  printf("Input: ");

  const char input = getchar();
  getchar(); // skip \n

  if(input < 49 || input > 56)
  {
     printf("Wrong input, try again\n");
     return menu();
  }

  return input;
}

int
main()
{
  auto parser = new file_parser();

  srand(time(NULL));

  while(true)
  {
     const int option = menu();

     switch(option)
     {
       case '1':
       {
         parser->clear();
         parser->get_filename();
         parser->parse_file();
       } break;

       case '2':
       {
          printf("!!!\n");
       } break;


       case '3':
       {
         parser->print_data();
       } break;

       case '4':
       {
       } break;

       case '5':
       {
       } break;

       case '6':
       {
       } break;

       case '7':
       {
       } break;

       case '8':
       {
         delete parser;
         return 0;
       }
     }
  }

}
