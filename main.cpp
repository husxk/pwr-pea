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
  printf("4. Brute force\n");
  printf("5. BB\n");
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

static int
get_size()
{
  int a;
  printf("\nInput size: ");
  std::cin >> a;
  getchar(); // skip \n
  return a;
}

int
main()
{
  auto parser = std::make_unique<file_parser>();
  auto alg = std::make_unique<graph>();

  srand(time(NULL));

  while(true)
  {
     const int option = menu();

     switch(option)
     {
       case '1':
       {
         parser.get()->clear();
         parser.get()->get_filename();
         parser.get()->parse_file();

         alg.get()->set(parser->get_size(), parser->get_input());
       } break;

       case '2':
       {
          auto size = get_size();
          if(size <= 0)
          {
            printf("\nSize must be >= 0! Try again!\n");
            continue;
          }

          parser.get()->generate_random(size);
          alg.get()->set(parser->get_size(), parser->get_input());

       } break;


       case '3':
       {
         parser.get()->print_data();
       } break;

       case '4':
       {
         alg.get()->brute_force();
         alg.get()->print();
       } break;

       case '5':
       {
          alg.get()->bb();
          alg.get()->print();
       } break;

       case '6':
       {
       } break;

       case '7':
       {
       } break;

       case '8':
       {
         return 0;
       }
     }
  }

}
