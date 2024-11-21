// 5. University awards gold medals to the student who has scored highest CGPA.Write
//     a program to find the student with highest CGPA in a list of numbers using OpenMP.
//     PROGRAM :
#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;
int main()
{
    int num_students;
    cout << "Enter number of students: ";
    cin >> num_students;
    vector<double> CGPA(num_students);
    cout << "Enter the CGPAs of the students:\n";
    for (double &cgpa : CGPA)
        cin >> cgpa;
    double max_cgpa_serial = CGPA[0], max_cgpa_parallel = CGPA[0];
    // Serial execution
    double start_serial = omp_get_wtime();
    for (int i = 0; i < num_students; i++)
        if (CGPA[i] > max_cgpa_serial)
            max_cgpa_serial = CGPA[i];
    double end_serial = omp_get_wtime();
    // Parallelexecution
    double start_parallel = omp_get_wtime();
#pragma omp parallel forshared(CGPA, max_cgpa_parallel)
    for (int i = 0; i < num_students; i++)
    {
#pragma omp critical
        {
            if (CGPA[i] > max_cgpa_parallel)
                max_cgpa_parallel = CGPA[i];
        }
    }
    double end_parallel = omp_get_wtime();
    cout << "HighestCGPA(Serial):" << max_cgpa_serial << "\n";
    cout << "SerialTime:" << end_serial - start_serial << "seconds\n";
    cout << "HighestCGPA(Parallel):" << max_cgpa_parallel << "\n";
    cout << "ParallelTime:" << end_parallel - start_parallel << "seconds\n";
    return 0;
}