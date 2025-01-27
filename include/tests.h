#pragma once
#include <chrono>
#include <cmath>
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

  // done with default params
  void
  run_sa()
  {
    std::cout << std::endl << "Running SA!\n";

    for(size_t j = 0; j < sa_arr.size(); j++)
    {
      auto elapsed = time_ms();

      for(int i = 0; i < N; i++)
      {
        parser.get()->generate_random(sa_arr[j]);
        alg.get()->set(parser.get()->get_size(), parser.get()->get_input());

        auto start = NOW();
        alg.get()->run_sa();
        auto end = NOW();

        elapsed += time_ms(end - start);
      }

      elapsed /= N;

      std::cout << std::endl << "SA loop for " << sa_arr[j] << ". time: "
        << elapsed.count() << "ms" << std::endl;
    }

    std::cout << std::endl << "SA PARAMS:" << std::endl 
    << "Temperature: " << SA::DEFAULT_TEMP << std::endl
    << "Iterations: " << SA::DEFAULT_ITERATIONS << std::endl
    << "Scale: " << SA::DEFAULT_SCALE << std::endl
    << "Count: n * n" << std::endl;
  }

  void
  run_genetic()
  {
    std::cout << std::endl << "Running genetic!\n";

    for(size_t j = 0; j < gen_arr.size(); j++)
    {
      auto elapsed = time_ms();

      for(int i = 0; i < N; i++)
      {
        parser.get()->generate_random(gen_arr[j]);
        alg.get()->set(parser.get()->get_size(), parser.get()->get_input());

        alg->set_genetic_params(0.1, 0.7);
        alg->set_pop(2500);
        alg->set_genetic_tournament(450);


        auto start = NOW();
        alg.get()->run_genetic();
        auto end = NOW();

        elapsed += time_ms(end - start);
      }

      elapsed /= N;

      std::cout << std::endl << "Genetic loop for " << sa_arr[j] << ". time: "
        << elapsed.count() << "ms" << std::endl;
    }

    std::cout << "End running genetic!\n";
  }

  // done with custom params
  // we are testing on 55.txt
  void
  run_sa_param_check()
  {
    constexpr int valid_res = 1608;
    constexpr char filename[] = "data/55.txt";
    constexpr int filename_size = sizeof(filename);

    parser->set_filename(filename, filename_size);
    parser->parse_file();

    std::cout << std::endl << "Running SA param check!";
    std::cout << std::endl << "Temp scale iters\n";

    for(const auto& temp : sa_arr_temp)
    {
      for(const auto& scale : sa_arr_scale)
      {
        for(const auto& iters : sa_arr_iters)
        {
            double diffs_p = 0;
            alg->set(parser->get_size(), parser->get_input());
            alg->set_sa(temp, iters, scale);

            for(int i = 0; i < N; i++)
            {
              alg->run_sa();
              int res = alg->get_result();

              const int diff = res - valid_res;
              diffs_p += std::abs((double) diff / valid_res);
            }

            const double av = diffs_p / N;

//            std::cout << "Ended SA calcs for " << temp << " "
//                      << scale << "  " << iters << " Result: "
//                      << av <<"\n";
            std::cout << temp << "," << scale << "," << iters << "," << av<< "\n";
        }
      }
    }
  }

  void
  run_sa_validity_check()
  {
    constexpr int valid_res0 = 39;
    constexpr char filename0[] = "data/17.txt";
    constexpr int filename0_size = sizeof(filename0);


    constexpr int valid_res1 = 1608;
    constexpr char filename1[] = "data/55.txt";
    constexpr int filename1_size = sizeof(filename1);

    constexpr int valid_res2 = 36230;
    constexpr char filename2[] = "data/124.txt";
    constexpr int filename2_size = sizeof(filename2);

    constexpr int temp  = 15000;
    constexpr int iters = 15000;
    constexpr double scale = 0.999;

    double av_time = 0;

    std::cout << std::endl << "Running SA validity check!";

    std::cout << std::endl << "File: " << filename0 << "\n";
    parser->set_filename(filename0, filename0_size);
    parser->parse_file();

    alg->set(parser->get_size(), parser->get_input());
    alg->set_sa(temp, iters, scale);

    double diffs_p = 0;
    alg->set(parser->get_size(), parser->get_input());
    alg->set_sa(temp, iters, scale);

    for(int i = 0; i < N; i++)
    {
      auto start = std::chrono::high_resolution_clock::now();
      alg->run_sa();
      auto end = std::chrono::high_resolution_clock::now();

      int res = alg->get_result();

      const int diff = std::abs(res - valid_res0);
      diffs_p += ((double) diff / valid_res0);

       av_time += 
             std::chrono::duration<double, std::milli>(end - start).count();
    }

    double av = diffs_p / N;

    std::cout << "Ended SA calcs for " << filename0 << " "
              << " Result: "
              << av << ", " << av_time/N << "\n";

    diffs_p = 0.0;
    av_time = 0.0;

    std::cout << std::endl << "File: " << filename1 << "\n";
    parser->set_filename(filename1, filename1_size);
    parser->parse_file();

    alg->set(parser->get_size(), parser->get_input());
    alg->set_sa(temp, iters, scale);

    alg->set(parser->get_size(), parser->get_input());
    alg->set_sa(temp, iters, scale);

    for(int i = 0; i < N; i++)
    {
      auto start = std::chrono::high_resolution_clock::now();
      alg->run_sa();
      auto end = std::chrono::high_resolution_clock::now();

      int res = alg->get_result();

      const int diff = std::abs(res - valid_res1);
      diffs_p += ((double) diff / valid_res1);

       av_time += 
             std::chrono::duration<double, std::milli>(end - start).count();
    }

    av = diffs_p / N;

    std::cout << "Ended SA calcs for " << filename1 << " "
              << " Result: "
              << av << ", " << av_time/N << "\n";

    diffs_p = 0.0;
    av_time = 0.0;

    std::cout << std::endl << "File: " << filename2 << "\n";
    parser->set_filename(filename2, filename2_size);
    parser->parse_file();

    alg->set(parser->get_size(), parser->get_input());
    alg->set_sa(temp, iters, scale);

    alg->set(parser->get_size(), parser->get_input());
    alg->set_sa(temp, iters, scale);

    for(int i = 0; i < N; i++)
    {
      auto start = std::chrono::high_resolution_clock::now();
      alg->run_sa();
      auto end = std::chrono::high_resolution_clock::now();

      int res = alg->get_result();

      const int diff = std::abs(res - valid_res2);
      diffs_p += ((double) diff / valid_res2);

       av_time += 
             std::chrono::duration<double, std::milli>(end - start).count();
    }

    av = diffs_p / N;

    std::cout << "Ended SA calcs for " << filename2 << " "
              << " Result: "
              << av << ", " << av_time/N << "\n";

  }

  // done with custom params
  // we are testing on 55.txt
  void
  run_gen_param_check()
  {
    constexpr int valid_res = 1608;
    constexpr char filename[] = "data/55.txt";
    constexpr int filename_size = sizeof(filename);

    parser->set_filename(filename, filename_size);
    parser->parse_file();

    std::cout << std::endl << "Running GENETIC param check!\n";

    for(const auto& size : gen_arr_pop_sizes)
    {
      for(const auto& mut : gen_arr_mut_params)
      {
        for(const auto& cross : gen_arr_cross_params)
        {
            double diffs_p = 0;
            double av_time = 0;

            alg->set(parser->get_size(), parser->get_input());
            alg->set_genetic_params(mut, cross);
            alg->set_pop(size);
            alg->set_genetic_tournament(300);

            for(int i = 0; i < N; i++)
            {
              auto start = std::chrono::high_resolution_clock::now();
              alg->run_genetic();
              auto end = std::chrono::high_resolution_clock::now();

              int res = alg->get_result();

              av_time += 
                   std::chrono::duration<double, std::milli>(end - start).count();

              const int diff = res - valid_res;
              diffs_p += std::abs((double) diff / valid_res);
            }

            const double av = diffs_p / N;
            av_time /= N;

            std::cout << size << "," << mut << "," << cross << "," << av
                      << "," << av_time << std::endl;
        }
        std::cout << std::endl;
      }

      std::cout << std::endl;
    }
  }

  void
  run_gen_validity_check()
  {
    constexpr int valid_res0 = 39;
    constexpr char filename0[] = "data/17.txt";
    constexpr int filename0_size = sizeof(filename0);


    constexpr int valid_res1 = 1608;
    constexpr char filename1[] = "data/55.txt";
    constexpr int filename1_size = sizeof(filename1);

    constexpr int valid_res2 = 36230;
    constexpr char filename2[] = "data/124.txt";
    constexpr int filename2_size = sizeof(filename2);

    constexpr int tour = 450;
    constexpr int pop = 2500;
    constexpr double cross = 0.7;
    constexpr double mut = 0.1;

    double av_time = 0;

    std::cout << std::endl << "Running genetic validity check!";

    std::cout << std::endl << "File: " << filename0 << "\n";
    parser->set_filename(filename0, filename0_size);
    parser->parse_file();

    alg->set(parser->get_size(), parser->get_input());
    alg->set_genetic_params(mut, cross);
    alg->set_pop(pop);
    alg->set_genetic_tournament(tour);


    double diffs_p = 0;

    for(int i = 0; i < N; i++)
    {
      auto start = std::chrono::high_resolution_clock::now();
      alg->run_genetic();
      auto end = std::chrono::high_resolution_clock::now();

      int res = alg->get_result();

      av_time += 
             std::chrono::duration<double, std::milli>(end - start).count();

      const int diff = std::abs(res - valid_res0);
      diffs_p += ((double) diff / valid_res0);
    }

    double av = diffs_p / N;

    std::cout << "Ended genetic calcs for " << filename0 << " "
              << " Result: "
              << av << "," << av_time/N << "\n";

    diffs_p = 0.0;
    av_time = 0.0;

    std::cout << std::endl << "File: " << filename1 << "\n";
    parser->set_filename(filename1, filename1_size);
    parser->parse_file();

    alg->set(parser->get_size(), parser->get_input());
    alg->set_genetic_params(mut, cross);
    alg->set_pop(pop);
    alg->set_genetic_tournament(tour);

    for(int i = 0; i < N; i++)
    {
      auto start = std::chrono::high_resolution_clock::now();
      alg->run_genetic();
      auto end = std::chrono::high_resolution_clock::now();

      int res = alg->get_result();

      av_time += 
             std::chrono::duration<double, std::milli>(end - start).count();

      const int diff = std::abs(res - valid_res1);
      diffs_p += ((double) diff / valid_res1);
    }

    av = diffs_p / N;

    std::cout << "Ended genetic calcs for " << filename1 << " "
              << " Result: "
              << av << "," << av_time/N << "\n";

    diffs_p = 0.0;
    av_time = 0.0;

    std::cout << std::endl << "File: " << filename2 << "\n";
    parser->set_filename(filename2, filename2_size);
    parser->parse_file();

    alg->set(parser->get_size(), parser->get_input());
    alg->set_genetic_params(mut, cross);
    alg->set_pop(pop);
    alg->set_genetic_tournament(tour);

    for(int i = 0; i < N; i++)
    {
      auto start = std::chrono::high_resolution_clock::now();
      alg->run_genetic();
      auto end = std::chrono::high_resolution_clock::now();

      int res = alg->get_result();

      av_time += 
             std::chrono::duration<double, std::milli>(end - start).count();

      const int diff = std::abs(res - valid_res2);
      diffs_p += ((double) diff / valid_res2);
    }

    av = diffs_p / N;

    std::cout << "Ended genetic calcs for " << filename2 << " "
              << " Result: "
              << av << "," << av_time/N << "\n";
  }

  void
  run_gen_iter_check()
  {
    constexpr int valid_res = 1608;
    constexpr char filename[] = "data/55.txt";
    constexpr int filename_size = sizeof(filename);

    parser->set_filename(filename, filename_size);
    parser->parse_file();

    std::cout << std::endl << "Running GENETIC iter check!\n";

    for(const auto& t : gen_arr_iter_sizes)
    {
            double diffs_p = 0;
            double av_time = 0;

            alg->set(parser->get_size(), parser->get_input());
            alg->set_genetic_params(0.1, 0.7);
            alg->set_pop(2500);
            alg->set_genetic_tournament(300);
            alg->set_genetic_iters(t);

            for(int i = 0; i < N; i++)
            {
              auto start = std::chrono::high_resolution_clock::now();
              alg->run_genetic();
              auto end = std::chrono::high_resolution_clock::now();

              int res = alg->get_result();

              av_time += 
                   std::chrono::duration<double, std::milli>(end - start).count();

              const int diff = res - valid_res;
              diffs_p += std::abs((double) diff / valid_res);
            }

            const double av = diffs_p / N;
            av_time /= N;

            std::cout << t << "," << av << "," << av_time << '\n';
    }
  }



  void
  run_gen_tour_check()
  {
    constexpr int valid_res = 1608;
    constexpr char filename[] = "data/55.txt";
    constexpr int filename_size = sizeof(filename);

    parser->set_filename(filename, filename_size);
    parser->parse_file();

    std::cout << std::endl << "Running GENETIC tournament check!\n";

    for(const auto& t : gen_arr_tour_sizes)
    {
            double diffs_p = 0;
            double av_time = 0;

            alg->set(parser->get_size(), parser->get_input());
            alg->set_genetic_params(0.1, 0.7);
            alg->set_pop(2500);
            alg->set_genetic_tournament(t);
            alg->set_genetic_iters(1000);

            for(int i = 0; i < N; i++)
            {
              auto start = std::chrono::high_resolution_clock::now();
              alg->run_genetic();
              auto end = std::chrono::high_resolution_clock::now();

              int res = alg->get_result();

              av_time += 
                   std::chrono::duration<double, std::milli>(end - start).count();

              const int diff = res - valid_res;
              diffs_p += std::abs((double) diff / valid_res);
            }

            const double av = diffs_p / N;
            av_time /= N;

            std::cout << t << "," << av << "," << av_time << '\n';
    }
  }

public:

  void
  run()
  {
  //  run_bf();
  //  run_bb();
  //  run_sa();
  //  run_sa_param_check();
    run_sa_validity_check();
  //  run_gen_param_check();
  //  run_gen_tour_check();
  //  run_gen_validity_check();
  //  run_genetic();
  //  run_gen_iter_check();
  }

private:
  static const int N = 20;

  std::vector<int> bb_arr = {10, 12, 14, 16, 18, 19, 21};
  std::vector<int> bf_arr = {4, 6, 8, 10, 11, 12, 13};
  std::vector<int> sa_arr = {40, 50, 60, 70, 80, 90, 100};
  std::vector<int> gen_arr = {40, 50, 60, 70, 80, 90, 100};

  std::vector<int> sa_arr_temp = {5000, 10000, 15000};
  std::vector<double> sa_arr_scale = {0.9, 0.99, 0.999};
  std::vector<int> sa_arr_iters = {5000, 10000, 15000};

  std::vector<int> gen_arr_pop_sizes       = {2500, 5000, 7500};
  std::vector<double> gen_arr_mut_params   = {0.01, 0.05, 0.1};
  std::vector<double> gen_arr_cross_params = {0.7, 0.8, 0.9};
  std::vector<double> gen_arr_tour_sizes = {150, 300, 450};
  std::vector<double> gen_arr_iter_sizes = {1000, 3000, 4500};

  std::unique_ptr<file_parser> parser = std::make_unique<file_parser>();
  std::unique_ptr<graph> alg = std::make_unique<graph>();
};
