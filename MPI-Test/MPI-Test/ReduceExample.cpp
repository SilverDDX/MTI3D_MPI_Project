// MPI-Test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <mpi.h>
#include<iostream>
using namespace std;

double h, n, sum, x, mypi, pi;
int myid;

int main(int argc, char **argv)
{
	
	int rank, numprocs;
	int pause;
	double PI25DT = 3.141592653589793238462643;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	if (myid == 0) {
		n = 1000000;
	}

	h = 1.0 / double(n);
	sum = 0.0;

	for (int i = myid + 1; i <= n; i += numprocs) {
		x = h * (double(i) - 0.5);
		sum += 4.0 / (1.0 + x * x);
	}

	mypi = h * sum;

	MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (myid == 0) {
		cout << "pi is approximately: " << pi << endl;
			cout << "error is :" << fabs(pi-PI25DT) << endl;
	}

	cin >> pause;

	MPI_Finalize();

	return 0;
}
