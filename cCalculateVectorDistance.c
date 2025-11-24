#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define SIZE 

extern void asmCalculateVectorDistance(size_t n, double *x1, double *x2, double *y1, double *y2, double *z);

void cCalculateVectorDistance(size_t n, double *x1, double *x2, double *y1, double *y2, double *z){
	size_t i;
	for(i = 0; i < n; i++){
		double dx = x2[i] - x1[i];
		double dy = y2[i] - y1[i];
		z[i] = sqrt(dx * dx + dy * dy);
	}
}

int main(){
	
	clock_t start, end;
	double timeC20;
	double timeASM20;
	double timeC24;
	double timeASM24;
	double timeC28;
	double timeASM28;
	int i;
	size_t n;
	size_t n20 = 1UL << 20; // 2^20
	size_t n24 = 1UL << 24; // 2^24
	size_t n28 = 1UL << 28; // 2^28; my machine cannot handle 2^30 due to memory limits

	double *x1 = (double*)malloc(n28 * sizeof(double));
	double *x2 = (double*)malloc(n28 * sizeof(double));
	double *y1 = (double*)malloc(n28 * sizeof(double));
	double *y2 = (double*)malloc(n28 * sizeof(double));
	double *z  = (double*)malloc(n28 * sizeof(double));
	
	if (!x1 || !x2 || !y1 || !y2 || !z) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
	
	// Initialize arrays
	x1[0] = 1.5; x1[1] = 4.0; x1[2] = 3.5; x1[3] = 2.0; // test values from specs
    x2[0] = 3.0; x2[1] = 2.5; x2[2] = 2.5; x2[3] = 1.0; // test values from specs
    y1[0] = 4.0; y1[1] = 3.0; y1[2] = 3.5; y1[3] = 3.0; // test values from specs
    y2[0] = 2.0; y2[1] = 2.5; y2[2] = 1.0; y2[3] = 1.5; // test values from specs

	for (i = 4; i < n; i++) {
    x1[i] = 1.0 + ((double)rand() / RAND_MAX) * 4.0; // 1.0 to 5.0
    x2[i] = 1.0 + ((double)rand() / RAND_MAX) * 4.0;
    y1[i] = 1.0 + ((double)rand() / RAND_MAX) * 4.0;
    y2[i] = 1.0 + ((double)rand() / RAND_MAX) * 4.0;
	}

	printf("\n");
	printf("Vector Values:\n");
	printf("X1: ");
	for (i = 0; i < 10; i++) {
		printf("%.1f, ", x1[i]);
	}
	printf(" ...\n");

	printf("X2: ");
	for (i = 0; i < 10; i++) {
		printf("%.1f, ", x2[i]);
	}
	printf(" ...\n");

	printf("Y1: ");
	for (i = 0; i < 10; i++) {
		printf("%.1f, ", y1[i]);
	}
	printf(" ...\n");

	printf("Y2: ");
	for (i = 0; i < 10; i++) {
		printf("%.1f, ", y2[i]);
	}
	printf(" ...\n\n");
	
	//--------------------------------------------------- n = 2^20 ---------------------------------------------------//
	n = n20;

	printf("FIRST TEN VALUES OF Z (C):\n");
	start = clock(); //timer start
	cCalculateVectorDistance(n, x1, x2, y1, y2, z);
	end = clock(); //timer end
	printf("Z: ");
	for (i = 0; i < 10; i++) {
		printf("%.8f, ", z[i]);
	}
	printf(" ...\n\n");
	timeC20 = (double) (end - start) / CLOCKS_PER_SEC;

	printf("FIRST TEN VALUES OF Z (ASM)\n");
	start = clock(); //timer start
	asmCalculateVectorDistance(n, x1, x2, y1, y2, z);
	end = clock(); //timer end
	printf("Z: ");
	for (i = 0; i < 10; i++) {
		printf("%.8f, ", z[i]);
	}
	printf(" ...\n\n");

	printf("n = 2^20\n");
	printf("Execution time (C): %.8fs\n", timeC20);
	
	timeASM20 = (double) (end - start) / CLOCKS_PER_SEC;
	printf("Execution time (ASM): %.8fs\n", timeASM20);

	printf("Difference (C - ASM): %.8fs\n", timeC20 - timeASM20);
	printf("Speedup (C/ASM): %.2f\n", timeC20 / timeASM20);

	//--------------------------------------------------- n = 2^24 ---------------------------------------------------//

	n = n24;

	printf("\n");
	start = clock(); //timer start
	cCalculateVectorDistance(n, x1, x2, y1, y2, z);
	end = clock(); //timer end
	
	timeC24 = (double) (end - start) / CLOCKS_PER_SEC;
	printf("n = 2^24\n");
	printf("Execution time (C): %.8fs\n", timeC24);

	start = clock(); //timer start
	asmCalculateVectorDistance(n, x1, x2, y1, y2, z);
	end = clock(); //timer end
	
	timeASM24 = (double) (end - start) / CLOCKS_PER_SEC;
	printf("Execution time (ASM): %.8fs\n", timeASM24);

	printf("Difference (C - ASM): %.8fs\n", timeC24 - timeASM24);
	printf("Speedup (C/ASM): %.2f\n", timeC24 / timeASM24);

	//--------------------------------------------------- n = 2^28 ---------------------------------------------------//
	n = n28;

	printf("\n");

	start = clock(); //timer start
	cCalculateVectorDistance(n, x1, x2, y1, y2, z);
	end = clock(); //timer end
	
	timeC28 = (double) (end - start) / CLOCKS_PER_SEC;
	printf("n = 2^28\n");
	printf("Execution time (C): %.8fs\n", timeC28);


	start = clock(); //timer start
	asmCalculateVectorDistance(n, x1, x2, y1, y2, z);
	end = clock(); //timer end

	timeASM28 = (double) (end - start) / CLOCKS_PER_SEC;
	printf("Execution time (ASM): %.8fs\n", timeASM28);

	printf("Difference (C - ASM): %.8fs\n", timeC28 - timeASM28);
	printf("Speedup (C/ASM): %.2f\n", timeC28 / timeASM28);

	free(x1);
    free(x2);
    free(y1);
    free(y2);
    free(z);

	return 0;
}
