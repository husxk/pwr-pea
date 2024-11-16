#pragma once
#include <chrono>
#include <iostream>

#include "file_parser.h"
#include "graph.h"

#define NOW() \
        std::chrono::high_resolution_clock::now()

class tests
{
  using time_ms = std::chrono::duration<float, std::chrono::milliseconds::period>;
private:

  void
  run_bf()
  {
    std::cout << std::endl << "Running brute force!\n";


    for(size_t j = 0; j < bf_arr.size(); j++)
    {
      auto elapsed = time_ms();

      for(int i = 0; i < N; i++)
      {
        parser.get()->generate_random(bf_arr[j]);
        alg.get()->set(parser.get()->get_size(), parser.get()->get_input());

        auto start = NOW();
        alg.get()->brute_force();
        auto end = NOW();

        elapsed += time_ms(end - start);
      }

      elapsed /= N;

      std::cout << std::endl << "BF loop for " << bf_arr[j] << ". time: "
        << elapsed.count() << "ms" << std::endl;
    }
  }

  void
  run_bb()
  {
    std::cout << std::endl << "Running BB!\n";

    for(size_t j = 0; j < bb_arr.size(); j++)
    {
      auto elapsed = time_ms();

      for(int i = 0; i < N; i++)
      {
        parser.get()->generate_random(bb_arr[j]);
        alg.get()->set(parser.get()->get_size(), parser.get()->get_input());

        auto start = NOW();
        alg.get()->bb();
        auto end = NOW();

        elapsed += time_ms(end - start);
      }

      elapsed /= N;

      std::cout << std::endl << "BB loop for " << bb_arr[j] << ". time: "
        << elapsed.count() << "ms" << std::endl;
    }
  }

public:

  void
  run()
  {
    run_bf();
    run_bb();
  }

private:
  static const int N = 20;

  std::vector<int> bb_arr = {10, 12, 14, 16, 18, 19, 21};
  std::vector<int> bf_arr = {4, 6, 8, 10, 11, 12, 13};

  std::unique_ptr<file_parser> parser = std::make_unique<file_parser>();
  std::unique_ptr<graph> alg = std::make_unique<graph>();
};
