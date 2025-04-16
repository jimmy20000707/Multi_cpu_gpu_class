#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NX 20
#define NY 10     //number of grid points
#define NT 1000000    //number of time steps
#define DX 0.1
#define DY 0.1   //space between points
#define DT 0.001   //time step
#define ALPHA 0.00001173 //Thermal diffusivity

double** allocate_2d_memory();  //allocate memory
void free_2d_memory(double** T);//free memory
void init(double** T);  //initialize
void caculate(double** T,double** T_new,double alpha,double dt,double dx,double dy); //caculate new tempterature
void update(double** T,double** T_new);  //update tempterature
void print_temperature(double** T); //print

int main(){
	double** T = allocate_2d_memory();
	double** T_new = allocate_2d_memory();

	int no_threads=4;
	omp_set_num_threads(no_threads);

	init(T);
	init(T_new);
	for(int step=0;step<=NT;step++){
		caculate(T, T_new, ALPHA, DT, DX ,DY);
		update(T,T_new);
		//printf("time = %.4f\n",time);
		//print_temperature(T);
	}

	print_temperature(T);

	free_2d_memory(T);
	free_2d_memory(T_new);
	return 0;
}

double** allocate_2d_memory() {
    double** array = (double**)malloc(NX * sizeof(double*));
    for (int i = 0; i < NX; i++) {
        array[i] = (double*)malloc(NY * sizeof(double));
    }
    return array;
}

void free_2d_memory(double** T) {
    for (int i = 0; i < NX; i++) {
        free(T[i]);
    }
    free(T);
}

void init(double** T){
	//I.C
	for(int i=0;i<NX;i++){
		for(int j=0;j<NY;j++){
			T[i][j]=0.0;
		}
	}

	//B.C
	for (int i = 0; i < NX; i++) {
                T[i][0] = 0.0;  //Left
                T[i][NY-1] = 1.0;//Right
        }
        for (int j = 0; j < NY; j++) {
                T[0][j] = 0.0;    //Up
                T[NX-1][j] = 0.0;//Down
        }
}

void caculate(double** T,double** T_new,double alpha,double dt,double dx,double dy){
	#pragma omp parallel for collapse(2)
	for(int i=1;i<NX-1;i++){
		for(int j=1;j<NY-1;j++){
			T_new[i][j]=T[i][j]
			+alpha*dt*((T[i+1][j]+T[i-1][j]-2*T[i][j])/(dx*dx)
			+(T[i][j+1]+T[i][j-1]-2*T[i][j])/(dy*dy));
		}
	}
}
void update(double** T,double ** T_new){
	for (int i = 0; i < NX; i++){
		for (int j = 0; j < NY; j++){
            		T[i][j] = T_new[i][j];
		}
    	}
}

void print_temperature(double** T){
	double time=NT*DT;
	printf("Time=%g\n",time);
	printf("Thermal diffusivity=%g\n",ALPHA);
    	for(int i = 0; i < NX; i++) {
        	for(int j = 0; j < NY; j++) {
            	printf("%.3f\t", T[i][j]);
        }
        printf("\n");
    }
}
