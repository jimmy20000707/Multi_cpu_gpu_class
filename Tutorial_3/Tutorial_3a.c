#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000
#define T 100
#define PHI 0.1

void Init(double *a){
	for(int i=0;i<N;i++){
		if(i<0.5*N){
			a[i]=0;
		}
		else{
			a[i]=1;
		}
	}
}

void Calc(double *a,double *b){
	int i =0;
	double L;
	double R;
	for(i=0; i<N; i++){
       		L = (i == 0) ? a[i] : a[i - 1];
        	R = (i == N-1) ? a[i] : a[i + 1];
        	b[i] = a[i] + PHI * (L + R - 2 * a[i]);
   	}

	for(i=0;i<N;i++){
		a[i]=b[i];
	}
}

void Save(double *a, double *b) {
    FILE *file = fopen("output.txt", "w");
    if (file == NULL){
        printf("Can not open file\n");
        return;
    }

    fprintf(file, "Index\tA\tB\n");
    for (int i = 0; i < N; i++) {
        fprintf(file, "%d\t%.4f\t%.4f\n", i, a[i], b[i]);
    }

    fclose(file);
    printf("save to output.txt\n");
}

int main(){
        double *a=(double *)malloc(N*sizeof(double));
        double *b=(double *)malloc(N*sizeof(double));
	if (a == NULL || b == NULL){
		printf("MEMORY  ERROR");
		return 1;
	}

        Init(a);
        for(int i=0;i<T;i++){
                Calc(a, b);
        }

	Save(a, b);
        free(a);
        free(b);
	return 0;
}

