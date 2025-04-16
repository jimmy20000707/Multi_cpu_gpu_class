#include <stdio.h>
#include <stdlib.h>

#define K1 0.5
#define K2 1.0
#define K3 1.5
#define K4 2.0
#define K5 2.5


#define M 1

#define DT 0.0001

void Compute_Accelerations(double x1, double x2, double x3, double x4,double acc[4]) {
	acc[0] = (-(K1+K2) * x1 + K2 * x2) / M;
	acc[1] = (K2 * x1 - (K2+K3) * x2 + K3 * x3) / M;
	acc[2] = (K3 * x2 - (K3+K4) * x3 + K4 * x4) / M;
	acc[3] = (K4 * x3 - (K4+K5) * x4 ) / M;
}

int main() {
	double x1 = 0.0, x2 = 1.0, x3 = 0.0, x4 = 0.0;
	double v1 = 0.0, v2 = 0.0, v3 = 0.0, v4 = 0.0;  // I.C.
	double acc[4];

	int steps = 50000;

	double *pos1 = (double *)malloc(steps * sizeof(double));
	double *pos2 = (double *)malloc(steps * sizeof(double));
	double *pos3 = (double *)malloc(steps * sizeof(double));
	double *pos4 = (double *)malloc(steps * sizeof(double));
	double *vel1 = (double *)malloc(steps * sizeof(double));
        double *vel2 = (double *)malloc(steps * sizeof(double));
        double *vel3 = (double *)malloc(steps * sizeof(double));
	double *vel4 = (double *)malloc(steps * sizeof(double));
        double *acc1 = (double *)malloc(steps * sizeof(double));
        double *acc2 = (double *)malloc(steps * sizeof(double));
        double *acc3 = (double *)malloc(steps * sizeof(double));
	double *acc4 = (double *)malloc(steps * sizeof(double));

        pos1[0] = x1; pos2[0] = x2; pos3[0] = x3; pos4[0]=x4;
        vel1[0] = v1; vel2[0] = v2; vel3[0] = v3; vel4[0]=v4;
	Compute_Accelerations(pos1[0], pos2[0], pos3[0],pos4[0], acc);
	acc1[0]=acc[0];acc2[0]=acc[1];acc3[0]=acc[2],acc4[0]=acc[3];
	FILE *file = fopen("spring_simulation.txt","w");
	//write file
	//fprintf(file, "Time(s)\tMass 1 pos\tMass 1 vel\tMass 1 acc\tMass 2 pos\tMass 2 vel\tMass 2 acc\tMass 3 pos\tMass 3 vel\tMass 3 acc\n");
	for(int t = 1; t < steps; t++){
                Compute_Accelerations(pos1[t-1], pos2[t-1], pos3[t-1],pos4[t-1], acc);

                acc1[t] = acc[0];
                acc2[t] = acc[1];
                acc3[t] = acc[2];
		acc4[t] = acc[3];

                vel1[t] = vel1[t - 1] + acc1[t] * DT;
                vel2[t] = vel2[t - 1] + acc2[t] * DT;
                vel3[t] = vel3[t - 1] + acc3[t] * DT;
		vel4[t] = vel4[t - 1] + acc4[t] * DT;

                pos1[t] = pos1[t - 1] + vel1[t] * DT;
                pos2[t] = pos2[t - 1] + vel2[t] * DT;
                pos3[t] = pos3[t - 1] + vel3[t] * DT;
		pos4[t] = pos3[t - 1] + vel4[t] * DT;

		fprintf(file, "%.4f\t %.4f\t %.4f\t %.4f\t\n", pos1[t], pos2[t], pos3[t], pos4[t]);
        }

	free(pos1); free(pos2); free(pos3); free(pos4);
	free(vel1); free(vel2); free(vel3); free(vel4);
	free(acc1); free(acc2); free(acc3); free(acc4);
	return 0;
}
