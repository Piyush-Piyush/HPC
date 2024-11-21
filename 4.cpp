#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main()
{
    int limit;
    cout << "Enter the number of terms in the Fibonacci series: ";
    cin >> limit;

    if (limit < 1)
    {
        cout << "Please enter a positive number!" << endl;
        return 0;
    }

    vector<int> fib_series(limit);
    int count = 0;

#pragma omp parallel sections shared(fib_series, count, limit)
    {
// Section for generating Fibonacci series
#pragma omp section
        {
            int a = 0, b = 1, c;
            if (limit >= 1)
            {
#pragma omp critical
                fib_series[count++] = a;
            }
            if (limit >= 2)
            {
#pragma omp critical
                fib_series[count++] = b;
            }
            for (int i = 2; i < limit; ++i)
            {
                c = a + b;
#pragma omp critical
                fib_series[count++] = c;
                a = b;
                b = c;
            }
        }

// Section for printing Fibonacci series
#pragma omp section
        {
            int printed = 0;
            while (printed < limit)
            {
#pragma omp critical
                if (printed < count)
                {
                    cout << fib_series[printed] << " ";
                    ++printed;
                }
            }
            cout << endl;
        }
    }

    return 0;
}
