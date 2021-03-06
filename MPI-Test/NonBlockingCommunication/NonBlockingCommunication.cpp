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
	MPI_Request reqs[4];



	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	if (myid == 0) {

		for (int i = myid; i <= n; i += numprocs) {
			x = h * (double(i) - 0.5);
			sum += 4.0 / (1.0 + x * x);

		}

		MPI_Isend(&sum, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &reqs[0]);
		MPI_Wait(&reqs[0], MPI_STATUS_IGNORE);

	}

	if (myid == 1) {
		MPI_Irecv(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &reqs[0]);
		for (int i = myid; i <= n; i += numprocs) {

			x = h * (double(i) - 0.5);
			sum += 4.0 / (1.0 + x * x);

		}
		MPI_Isend(&sum, 1, MPI_DOUBLE, 2, 0, MPI_COMM_WORLD, &reqs[1]);
		MPI_Wait(&reqs[1], MPI_STATUS_IGNORE);

	}

	if (myid == 2) {
		MPI_Irecv(&sum, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &reqs[1]);
		for (int i = myid; i <= n; i += numprocs) {

			x = h * (double(i) - 0.5);
			sum += 4.0 / (1.0 + x * x);

		}
		MPI_Isend(&sum, 1, MPI_DOUBLE, 2, 0, MPI_COMM_WORLD, &reqs[2]);
		MPI_Wait(&reqs[2], MPI_STATUS_IGNORE);
	}

	if (myid == 3) {
		MPI_Irecv(&sum, 1, MPI_DOUBLE, 2, 0, MPI_COMM_WORLD,  &reqs[2]);
		for (int i = myid; i <= n; i += numprocs) {

			x = h * (double(i) - 0.5);
			sum += 4.0 / (1.0 + x * x);
		}
		mypi = h * sum;
		cout << "pi = " << mypi << endl;
		cout << "error : " << mypi - PI25DT << endl;

	}


	MPI_Finalize();



	return 0;
}
