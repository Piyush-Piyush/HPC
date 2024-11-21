//  2. Consider a Scenario where a person visits a supermarket for shopping. He
//  purchases various items in different sections such as clothing, gaming, grocery,
//  stationary. Write an openMP program to process his bill parallelly in each section and
//  display the final amount to be paid. (sum of elements parallelly)
//  PROGRAM:              

#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

// Function to calculate prices serially
void calculateSerial(const vector<string> &sections, vector<int> &prices_serial)
{
    for (int i = 0; i < sections.size(); ++i)
    {
        int num_items;
        cout << "Enter the number of items for " << sections[i] << " (Serial): ";
        cin >> num_items;
        cout << "Enter the prices of items for " << sections[i] << ":\n";
        int total = 0;
        for (int j = 0; j < num_items; ++j)
        {
            int price;
            cin >> price;
            total += price;
        }
        prices_serial[i] = total;
    }
}

// Function to calculate prices in parallel
void calculateParallel(const vector<string> &sections, vector<int> &prices_parallel)
{
    for (int i = 0; i < sections.size(); ++i)
    {
        int num_items;
        cout << "Enter the number of items for " << sections[i] << " (Parallel): ";
        cin >> num_items;
        cout << "Enter the prices of items for " << sections[i] << ":\n";
        vector<int> items(num_items);
        for (int j = 0; j < num_items; ++j)
        {
            cin >> items[j];
        }
        int total = 0;
#pragma omp parallel for reduction(+ : total)
        for (int j = 0; j < num_items; ++j)
        {
            total += items[j];
        }
        prices_parallel[i] = total;
    }
}

int main()
{
    vector<string> sections = {"Clothing", "Gaming", "Grocery", "Stationery"};
    vector<int> prices_serial(sections.size(), 0);
    vector<int> prices_parallel(sections.size(), 0);

    // Serial Execution
    cout << "Serial Execution:\n";
    double start_serial = omp_get_wtime();
    calculateSerial(sections, prices_serial);
    double end_serial = omp_get_wtime();

    // Parallel Execution
    cout << "\nParallel Execution:\n";
    double start_parallel = omp_get_wtime();
    calculateParallel(sections, prices_parallel);
    double end_parallel = omp_get_wtime();

    // Results
    int total_serial = 0, total_parallel = 0;
    cout << "\nResults (Serial):\n";
    for (int i = 0; i < sections.size(); ++i)
    {
        cout << sections[i] << ": " << prices_serial[i] << "\n";
        total_serial += prices_serial[i];
    }
    cout << "Total Cost (Serial): " << total_serial << "\n";
    cout << "Serial Time: " << end_serial - start_serial << " seconds\n";

    cout << "\nResults (Parallel):\n";
    for (int i = 0; i < sections.size(); ++i)
    {
        cout << sections[i] << ": " << prices_parallel[i] << "\n";
        total_parallel += prices_parallel[i];
    }
    cout << "Total Cost (Parallel): " << total_parallel << "\n";
    cout << "Parallel Time: " << end_parallel - start_parallel << " seconds\n";

    return 0;
}
