// MPI-Test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <mpi.h>
#include<iostream>
using namespace std;


int main(int argc, char **argv)
{
	double h, n, sum, x, mypi, pi;
	double PI25DT = 3.141592653589793238462643;
	int myid, numprocs;
	int pause;
	n = 1000000;
	h = 1.0 / double(n);
	sum = 0.0;


	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	if (myid == 0) {

		for (int i = myid; i <= n; i += numprocs) {
			x = h * (double(i) - 0.5);
			sum += 4.0 / (1.0 + x * x);
	
		}

		MPI_Send(&sum, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
	
	}

	if (myid == 1) {
		MPI_Recv(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		for (int i = myid; i <= n; i += numprocs) {
	
			x = h * (double(i) - 0.5);
			sum += 4.0 / (1.0 + x * x);

		}
		MPI_Send(&sum, 1, MPI_DOUBLE, 2, 0, MPI_COMM_WORLD);
	
	}

	if (myid == 2) {
		MPI_Recv(&sum, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		for (int i = myid; i <= n; i += numprocs) {
	
			x = h * (double(i) - 0.5);
			sum += 4.0 / (1.0 + x * x);
		
		}
		MPI_Send(&sum, 1, MPI_DOUBLE, 3, 0, MPI_COMM_WORLD);
	}

	if (myid == 3) {
		MPI_Recv(&sum, 1, MPI_DOUBLE, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		for (int i = myid; i <= n; i += numprocs) {
			
			x = h * (double(i) - 0.5);
			sum += 4.0 / (1.0 + x * x);
		}
		
	}

	if (myid == 3) {
		mypi = h * sum;
		cout << "pi = " << mypi<<endl;
		cout << "error : " << mypi - PI25DT << endl;
	}
	
	MPI_Finalize();

	

	return 0;
}
