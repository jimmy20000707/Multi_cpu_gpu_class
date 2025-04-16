#include <stdio.h>
#include <math.h>
#include <omp.h>

#define N 5
#define NX (N*N)
#define MAX_ITER 1

void mat_vec_mul(double A[NX*NX], double x[NX], double y[NX]) {
    for (int i = 0; i < N; i++) {
        y[i] = 0.0;
        for (int j = 0; j < N; j++) {
            y[i] += A[i * N + j] * x[j];
        }
    }

}

void vec_scalar_mul(double alpha, double *x, double *y) {
    for (int i = 0; i < N; i++) {
        y[i] = alpha * x[i];
    }
}

void vec_sub(double *x, double *y, double *z) {
    for (int i = 0; i < N; i++) {
        z[i] = x[i] - y[i];
    }
}

void vec_add(double *x, double *y, double *z) {
    for (int i = 0; i < N; i++) {
        z[i] = x[i] + y[i];
    }
}

double vec_dot(double *x, double *y) {
    double result = 0;
    for (int i = 0; i < N; i++) {
        result += x[i] * y[i];
    }
    return result;
}

void cg_method(double A[NX * NX], double b[NX], double x[NX]){
    double r[NX], p[NX], Ap[NX];
    double alpha, beta;
    double r_s_old = 0, r_s_new;

    // 初始化
    for (int i = 0; i < NX; i++) {
        x[i] = 0;
        r[i] = b[i];
        p[i] = r[i];
	//printf("r[%d]=%.2f\n",i,r[i]);
    }

    for (int iter = 0; iter < MAX_ITER; iter++) {
        double pAp = 0;
        r_s_new = 0; // 初始化 r_s_new

        // Ap
	double Ap[NX]={0};
	for(int i = 0; i < N; i++){
        	p[i] = 0.0;
        	for (int j = 0; j < N; j++){
            		Ap[i] += A[i * N + j] * p[j];
        	}
    	}
	for(int i=0;i<NX;i++){printf("Ap[%d]=%.2f\n",i,Ap[i]);}
        // p^T * Ap
        pAp = vec_dot(p, Ap);

	//rTr
	r_s_old = vec_dot(r,r);

        //alpha
        alpha = r_s_old / pAp;

        // update x, r
        double alpha_p[NX],new_x[NX];
        vec_scalar_mul(alpha, p, alpha_p);
        vec_add(x, alpha_p, new_x)
;
        double alpha_Ap[NX],new_r[NX];
        vec_scalar_mul(alpha, Ap, alpha_Ap);
        vec_sub(r, alpha_Ap, new_r);
	for (int i = 0; i < NX; i++){
                x[i] = new_x[i];
		r[i] = new_r[i];
        }

        //  r_s_new
        r_s_new = vec_dot(r, r);

        // 判断收敛
        if (sqrt(r_s_new) < 1e-6) {
            break;
        }

        // 计算 beta
        beta = r_s_new / r_s_old;

        // 更新 p
	double beta_p[NX],new_p[NX];
        vec_scalar_mul(beta, p, beta_p);
        vec_add(r, beta_p, new_p);
	for (int i = 0; i < NX; i++){
		p[i] = new_p[i];
	}

        r_s_old = r_s_new; // 更新 r_s_old
    }
    for(int i =0;i<NX;i++){
	printf("x[%d]=%.2f\n",i,x[i]);
    }
}

void init(double A[NX*NX] ,double b[NX]){
	///A
	for (int i = 0; i < NX*NX; i++) {
        A[i] = 0;
    	}
    	for (int i = 0; i < NX; i++) {
        	A[i * NX + i] = -4; // 主要對角線
        	if (i % N != N - 1) A[i * NX + (i + 1)] = 1; // 右邊相鄰
        	if (i % N != 0) A[i * NX + (i - 1)] = 1; // 左邊相鄰
        	if (i + N < NX) A[i * NX + (i + N)] = 1; // 下方相鄰
        	if (i - N >= 0) A[i * NX + (i - N)] = 1; // 上方相鄰
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

int main() {
    	double A[NX * NX];
    	double b[NX];
    	init(A,b);
	double x[NX];
   	cg_method(A, b, x);
    	return 0;
}
