//  4. Using OpenMP, Design and develop a multi-threaded program to generate and
//  printFibonacci Series. One thread must generate the numbers up to the specified limit
//  and another thread must print them. Ensure proper synchronization.
//  PROGRAM:
#include <iostream>
#include <omp.h>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

vector<int> fib;
bool ready = false;
#pragma omp threadprivate(ready) // Ensures thread safety for `ready`

void generate_fib(int limit)
{
    fib.push_back(0);
    if (limit > 1)
        fib.push_back(1);

    for (int i = 2; i < limit; i++)
    {
        fib.push_back(fib[i - 1] + fib[i - 2]);
    }

#pragma omp critical
    ready = true; // Signals that Fibonacci generation is complete
}

void print_fib()
{
    while (!ready)
    {
        // Busy-wait to ensure the Fibonacci sequence is generated
        this_thread::yield(); // Avoid aggressive CPU usage
    }

#pragma omp critical
    {
        cout << "Fibonacci Sequence: ";
        for (int val : fib)
            cout << val << " ";
        cout << endl;
    }
}

int main()
{
    int limit;
    cout << "Enter the limit for Fibonacci series: ";
    cin >> limit;

    // Serial Execution
    double start_serial = omp_get_wtime();
    fib.clear();
    generate_fib(limit);
    print_fib();
    double end_serial = omp_get_wtime();
    cout << "Serial Execution Time: " << end_serial - start_serial << " seconds\n";

    // Parallel Execution
    double start_parallel = omp_get_wtime();
#pragma omp parallel sections
    {
#pragma omp section
        generate_fib(limit);

#pragma omp section
        print_fib();
    }
    double end_parallel = omp_get_wtime();
    cout << "Parallel Execution Time: " << end_parallel - start_parallel << " seconds\n";

    return 0;
}
