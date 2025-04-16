#include <stdio.h>

#define ALPHA 1.1   //maximum prey per capita growth rate
#define BETA 0.4    //effect of the presence of predators on the prey death rate
#define GAMMA 0.4   //predator's per capita death rate
#define DELTA 0.1   //effect of the presence of prey on the predator's growth rate
#define DT 0.001

void Lotka_Volterra(float *x,float *y){
        float dx = (ALPHA*(*x))-(BETA*(*x)*(*y));
        float dy = -(GAMMA*(*y))+(DELTA*(*x)*(*y));
        printf("prey: %f\t predator: %f\t\n",*x,*y);
        *x=(dx*DT)+(*x);
        *y=(dy*DT)+(*y);
}

int main(){
        float x=10;
        float y=10;
        float T = 50.0;
	FILE *file = fopen("LK.txt","w");
        printf("prey: %f\t predator: %f\t\n",x,y);
        for(float t=0;t<100;t+=DT){
                Lotka_Volterra(&x,&y);
       		 //write file
		fprintf(file, "%.3f\t%.3f\t%.3f\n",t,x,y);
        }
	fclose(file);
	return 0;
}

