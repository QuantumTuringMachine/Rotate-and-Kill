#include <stdio.h>
#include <ctime>
#include <memory.h>

#include "MAT-A.h"
#include "MAT-K.h"
#include "MAT-CM.h"

const int maxn = 100000;
const int repeat = 10;

double x[maxn + 2], y[maxn + 2];

double computeMAT(const int n, const double x[], const double y[], int & a, int & b, int & c, int & T_iteration, const char code){
	switch (code){
		case 'A': return computeMAT_A(n, x, y, a, b, c, T_iteration);
		case 'K': return computeMAT_Kal(n, x, y, a, b, c, T_iteration);
		case 'C': return computeMAT_CM(n, x, y, T_iteration);
	}
	return 0;
}

char inFilename[7] = "?.in";
char outFilename[7] = "??.out";
char txtFilename[7] = "??.txt";

void testData(int testIndex, const char code){
	char inputfilename[7], outputfilename[7], iterationfilename[7];
	
	memcpy(inputfilename, inFilename, 7);
	inputfilename[0] = '0' + testIndex;

	memcpy(outputfilename, outFilename, 7);
	outputfilename[0] = '0' + testIndex;
	outputfilename[1] = code;

	memcpy(iterationfilename, txtFilename, 7);
	iterationfilename[0] = '0' + testIndex;
	iterationfilename[1] = code;

	FILE * fin = fopen(inputfilename, "r");  
	FILE * fout = fopen(outputfilename, "w");
	FILE * fit = fopen(iterationfilename, "w");

	int n, a, b, c, T_iteration, total_iteration = 0;
	double maxarea2;

	clock_t total_time = 0;  
	fscanf(fin, "%d", &n);

	while (n > 0){			
		for (int i = 1; i <= n; i++) fscanf(fin, "%lf%lf", &x[i], &y[i]);
		x[0] = x[n]; y[0] = y[n]; x[n + 1] = x[1]; y[n + 1] = y[1];

		clock_t start = clock();  	
		for (int i = 0; i < repeat; i++) 
			maxarea2 = computeMAT(n, x, y, a, b, c, T_iteration, code);
		clock_t stop = clock();
		total_time += stop - start;
		
		fprintf(fout, "%.0lf\n", maxarea2 / 2);
		fprintf(fit, "%d\n", T_iteration);
		fscanf(fin, "%d", &n); 
		total_iteration += T_iteration;
	}
	double durationTotal = ((double)(total_time)) / (CLK_TCK * repeat);
	printf("Alg %c: total iterations = %d;    (average) running time = %lf\n", code, total_iteration, durationTotal);
	fclose(fin); fclose(fout); fclose(fit);
}

int main(){
	for (int i = 1; i <= 7; i++){
		printf("experiment-test case %d\n", i);
		testData(i, 'A');
		testData(i, 'K');
		testData(i, 'C');
	}
}

	
