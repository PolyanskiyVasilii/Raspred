#include "pch.h"
#include <iostream>
#include <omp.h>

int main()
{

	int x = 0, available_threads = 0;

	std::cout << "Enter number row/columns" << std::endl;
	std::cin >> x;

	std::cout << omp_get_num_procs() << " available threads" << std::endl;
	std::cout << "Choose number of active threads: ";
	std::cin >> available_threads;
	std::cout << std::endl;

	omp_set_num_threads(available_threads);

	int** A = new int*[x];
	int** B = new int*[x];
	int** C = new int*[x];

	for (int i = 0; i < x; i++)
	{
		A[i] = new int[x];
		B[i] = new int[x];
		C[i] = new int[x];

		for (int j = 0; j < x; j++)
		{
			A[i][j] = rand() % 10;
			B[i][j] = rand() % 10;
			C[i][j] = 0;
		}
	}

	int start = omp_get_wtime();

#pragma omp parallel for
	for (int i = 0; i < x; i++)
	{

		for (int j = 0; j < x; j++)
		{
			for (int k = 0; k < x; k++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	std::cout << "Spent " << omp_get_wtime() - start << " seconds";
	return 0;
}
