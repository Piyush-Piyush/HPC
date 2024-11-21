#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter the number of terms in the Fibonacci series: ";
    cin >> n;

    if (n < 1)
    {
        cout << "Please enter a positive number!" << endl;
        return 0;
    }

    vector<int> fib_series(n);
    int count = 0;

#pragma omp parallel sections shared(fib_series, count, n)
    {
// Section for generating Fibonacci series
#pragma omp section
        {
            int a = 0, b = 1, c;
            if (n >= 1)
            {
#pragma omp critical
                fib_series[count++] = a;
            }
            if (n >= 2)
            {
#pragma omp critical
                fib_series[count++] = b;
            }
            for (int i = 2; i < n; ++i)
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
            while (printed < n)
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
