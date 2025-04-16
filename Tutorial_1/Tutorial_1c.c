#include <stdio.h>

#define K1 10.0
#define K2 15.0
#define K3 20.0
#define M1 2.0
#define M2 3.0
#define M3 6.0

void Compute_Accelerations(double x1, double x2, double x3,double acc[3]){
	acc[0] = (-K1*x1+K2*(x2-x1))/M1;
	acc[1] = (-K2*(x2-x1)+K3*(x3-x2))/M2;
	acc[2] = (-K3*(x3-x2))/M3;
}

int main(){
	double x1 =10.0;
	double x2 =15.0;
	double x3 =6.0;
	double acc[3];
	Compute_Accelerations(x1,x2,x3,acc);
	printf("Acceleration of M1:%f\n",acc[0]);
	printf("Acceleration of M2:%f\n",acc[1]);
	printf("Acceleration of M3:%f\n",acc[2]);
	return 0;
}
