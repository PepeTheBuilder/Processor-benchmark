#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <vector>
#include <chrono>

void calculateBBP(int thread_id, int num_threads, int num_iterations, double& partial_sum) {
    partial_sum = 0.0;
    for (int k = thread_id; k < num_iterations; k += num_threads) {
        double term = (1.0 / std::pow(16, k)) * (4.0 / (8 * k + 1) - 2.0 / (8 * k + 4) - 1.0 / (8 * k + 5) - 1.0 / (8 * k + 6));
        partial_sum += term;
    }
}

int main() { 
    int num_threads, precision;
    std::cout << "Enter the number of threads: ";
    std::cin >> num_threads;
    std::cout << "Enter the precision (number of iterations): ";
    std::cin >> precision;

    std::vector<std::thread> threads(num_threads);
    std::vector<double> partial_sums(num_threads);

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(calculateBBP, i, num_threads, precision, std::ref(partial_sums[i]));
    }

    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "\nTime taken: " << duration.count() << " milliseconds\n";
    std::cout << "(precision/num_threads)=" << (precision / num_threads) << '\n';
    std::cout << "Score: " << (precision/num_threads)/ (10 * duration.count()) <<'\n' <<'\n';


    //double pi = 0.0;
    //for (int i = 0; i < num_threads; ++i) {
    //    pi += partial_sums[i];
    //    std::cout << partial_sums[i] << '\n';
    //}
    return 0;
}



