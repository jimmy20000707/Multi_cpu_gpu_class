#include <stdio.h>
#include <stdlib.h>

#define K1 10.0
#define K2 20.0
#define K3 30.0

#define M1 1.0
#define M2 1.0
#define M3 1.0

#define DT 0.0001

void Compute_Accelerations(double x1, double x2, double x3, double acc[3]) {
	acc[0] = (-K1 * x1 + K2 * (x2 - x1)) / M1;
	acc[1] = (-K2 * (x2 - x1) + K3 * (x3 - x2)) / M2;
	acc[2] = (-K3 * (x3 - x2)) / M3;
}

int main() {
	double x1 = 0.0, x2 = 0.0, x3 = 0.1;
	double v1 = 0.0, v2 = 0.0, v3 = 0.0;  // I.C.
	double acc[3];

	int steps = 50000;

	double *pos1 = (double *)malloc(steps * sizeof(double));
	double *pos2 = (double *)malloc(steps * sizeof(double));
	double *pos3 = (double *)malloc(steps * sizeof(double));
	double *vel1 = (double *)malloc(steps * sizeof(double));
        double *vel2 = (double *)malloc(steps * sizeof(double));
        double *vel3 = (double *)malloc(steps * sizeof(double));
        double *acc1 = (double *)malloc(steps * sizeof(double));
        double *acc2 = (double *)malloc(steps * sizeof(double));
        double *acc3 = (double *)malloc(steps * sizeof(double));

        pos1[0] = x1; pos2[0] = x2; pos3[0] = x3;
        vel1[0] = v1; vel2[0] = v2; vel3[0] = v3;
	Compute_Accelerations(pos1[0], pos2[0], pos3[0], acc);
	acc1[0]=acc[0];acc2[0]=acc[1];acc3[0]=acc[2];
	FILE *file = fopen("spring_simulation.txt","w");
	//write file
	fprintf(file, "Time(s)\tMass 1 pos\tMass 1 vel\tMass 1 acc\tMass 2 pos\tMass 2 vel\tMass 2 acc\tMass 3 pos\tMass 3 vel\tMass 3 acc\n");
	for(int t = 1; t < steps; t++){
                Compute_Accelerations(pos1[t-1], pos2[t-1], pos3[t-1], acc);

                acc1[t] = acc[0];
                acc2[t] = acc[1];
                acc3[t] = acc[2];

                vel1[t] = vel1[t - 1] + acc1[t] * DT;
                vel2[t] = vel2[t - 1] + acc2[t] * DT;
                vel3[t] = vel3[t - 1] + acc3[t] * DT;

                pos1[t] = pos1[t - 1] + vel1[t] * DT;
                pos2[t] = pos2[t - 1] + vel2[t] * DT;
                pos3[t] = pos3[t - 1] + vel3[t] * DT;
		fprintf(file, "%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\n", 
                t * DT, pos1[t], vel1[t], acc1[t], pos2[t], vel2[t], acc2[t], pos3[t], vel3[t], acc3[t]);
        }

        // steps/10 
        printf("Time (s)    x1     x2     x3     v1     v2     v3     a1     a2     a3\n");
	for(int t = 0; t < steps; t += steps / 10){
    	printf("%.2f   %.2f  %.2f  %.2f  %.2f  %.2f  %.2f  %.2f  %.2f  %.2f\n",
           	t * DT, pos1[t], pos2[t], pos3[t], vel1[t], vel2[t], vel3[t], acc1[t], acc2[t], acc3[t]);
	}

	free(pos1); free(pos2); free(pos3);
	free(vel1); free(vel2); free(vel3);
	free(acc1); free(acc2); free(acc3);

	return 0;
}
