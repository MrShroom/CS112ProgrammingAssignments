#include "testhelpers.h"
#include <stdio.h>
#include <math.h>
#include <float.h>

void printMat(double * matrix)
{
	fprintf(stderr, "\n");
	for (size_t i = 0; i < 4; i++)
	{
		fprintf(stderr,"%8f %8f %8f %8f\n", matrix[i], matrix[i + 4], matrix[i + 8], matrix[i + 12]);

	}
}

int compareMat(double * matrix, double * matrix2)
{
	for (int i = 0; i < 16; i++)
	{
		if (fabs(matrix[i] -matrix2[i]) <= FLT_EPSILON)
			return 0;
	}
	return 1;
}
