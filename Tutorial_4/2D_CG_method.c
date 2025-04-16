#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 100
#define NX (N*N)
#define MAX_ITER 100

void cg_method(float A[NX * NX], double b[NX], double x[NX]){
    double r[NX], p[NX], Ap[NX];
    double pAp=0,r_s_old=0,r_s_new=0;
    int stop =0;
    // 初始化
    for (int i = 0; i < NX; i++) {
        x[i] = 0;
        r[i] = b[i];
        p[i] = r[i];
    }

    for (int iter = 0; iter < MAX_ITER; iter++) {
        // Ap
	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < NX; i++){
        		Ap[i] = 0.0;
        		for (int j = 0; j < NX; j++){
            			Ap[i] += A[i * NX + j] * p[j];
        		}
    		}
		// pTAp
		double pAp_local = 0;
		#pragma omp parallel for reduction(+:pAp_local)
		for (int i = 0;i<NX;i++){
			pAp_local += p[i] * Ap[i];
		}
		#pragma omp single
		pAp = pAp_local;

        	// rTr
		double r_s_old_local = 0;
		#pragma omp parallel for reduction(+:r_s_old_local)
		for (int i = 0;i<NX;i++){
			r_s_old_local += r[i] * r[i];
		}
		#pragma omp single
		r_s_old = r_s_old_local;

		// alpha
		double alpha = r_s_old / pAp;
		// new x
		#pragma omp for
		for (int i=0;i<NX;i++){
			x[i] += alpha * p[i];
		}
        	// new r
		#pragma omp for
		for (int i = 0; i < NX; i++) {
			r[i] -= alpha * Ap[i];
		}
        	//判断收敛
		#pragma omp single
		{
			if(sqrt(r_s_old)< 1e-6 ){
				stop = 1;
			}
		}
        	//beta
		double r_s_new_local = 0;
		#pragma omp parallel for reduction(+:r_s_new_local)
		for (int i = 0;i<NX;i++){
                	r_s_new_local += r[i] * r[i];
        	}
		#pragma omp single
		r_s_new = r_s_new_local;
		double beta = r_s_new/r_s_old;
        	//update p
		#pragma omp for
		for (int i = 0; i < NX; i++) {
			p[i] = r[i] + beta * p[i];
		}
    	}
	if(stop){
            printf("stop at %d iter\n", iter);
            break;
        }
    }

	//print
	for(int i =0;i<NX;i++){
		printf("x[%d]=%.2f\n",i,x[i]);
    	}
}

void init(float A[NX*NX] ,double b[NX]){
	//A
	for (int i = 0; i < NX*NX; i++) {
        A[i] = 0;
    	}
    	for (int i = 0; i < NX; i++) {
        	A[i * NX + i] = 4; // 主要對角線
        	if (i % N != N - 1) A[i * NX + (i + 1)] = -1; // 右邊相鄰
        	if (i % N != 0) A[i * NX + (i - 1)] = -1; // 左邊相鄰
        	if (i + N < NX) A[i * NX + (i + N)] = -1; // 下方相鄰
        	if (i - N >= 0) A[i * NX + (i - N)] = -1; // 上方相鄰
    	}
	/*
	for (int i = 0; i < NX; i++) {
        	for (int j = 0; j < NX; j++) {
            		printf("%.2f ", A[i * NX + j]);
        	}
        	printf("\n");
    	}
	*/
	///B
	for(int i=0;i< N;i++){
		for(int j=0;j < N;j++){
			int index = i * N +j;
			if(j == N-1){
				b[index] = 1;
			}
			else{
				b[index] = 0;
			}
		}
	}
	//Print(B[NX])
	/*
	for (int i=0;i<NX;i++){
		printf("b[%d]=%.2f\n",i,b[i]);
	}
	*/

}
int save(double x[NX]){
	FILE *file = fopen("matrix.txt", "w");
    	if (file == NULL) {
        	printf("無法打開文件！\n");
        	return 1;
    	}
    	for (int i = 0; i < NX; i++) {
		fprintf(file, "%.5f ",x[i]);
		fprintf(file, "\n");
        }
	fclose(file);
	printf("矩陣已成功寫入到 matrix.txt。\n");
}
int main() {
    	float *A = (float *)malloc(NX * NX * sizeof(float));
	if (A == NULL) {
    		printf("記憶體分配失敗！\n");
    		return -1;  // 返回錯誤代碼
	}
    	double b[NX];
    	init(A,b);
	double x[NX];
	omp_set_num_threads(10);
   	cg_method(A, b, x);
	free(A);
	//save(x);
    	return 0;
}
