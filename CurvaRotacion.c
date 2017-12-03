#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define bb 0.2497
#define bd 5.16
#define ad 0.3105
#define ah 64.3
#define Mgal 2.325*10**7
#define G 1

double chi;
int i;
double sqrt(double x);
double mb_walk[0];
double md_walk[0];
double mh_walk[0];
double l_walk[0];
double radio[301];
double vel_obs[301];
double likelihood(double hola[], double vel_model);
double funcion(double chao[],double mb, double md, double mh);
void caminata();

int main(void){
   
    double vel_model;
    double mb;
    double md;
    double mh;
    FILE *in;
    int i;
    double var1;
    double var2;
    int test;
    char filename[150]="radioialVelocities.dat";
    printf("writing to file: %s\n",filename);

    in=fopen(filename,"r");
    if(!in){
        printf("problems opening the file %s\n",filename);
        exit(1);
    }
    printf("Now I am reading\n");
    for (i=1;i<301;i++){
        fscanf(in,"%lf %lf \n", &var1, &var2);
        radio[i]= var1;
        vel_obs[i]=var2;
    }
    fclose(in);
    likelihood(vel_obs,vel_model);
    caminata();
}
double likelihood(double hola[],double vel_model){
    double suma=0;
    for(i=0;i<301;i++){
        suma= suma + pow((hola[i]-vel_model),2);
    }
    double chi=(1.0/2.0)*suma;
    return exp(-chi);
}

double funcion(double chao[],double mb, double md, double mh){
    double vel;
    for(i=0;i<301;i++){
        vel= (sqrt(mb)*chao[i])/pow((chao[i]*chao[i] + bb*bb),3/4) + (sqrt(md)*chao[i])/pow((chao[i]*chao[i] + ((bd+ad)*(bd+ad))),3/4) + (sqrt(mh))/pow((chao[i]*chao[i] + ah*ah),3/4);
    }
    return vel;
}


void caminata(){
    double suma=0;
    double y_init;
    double mb_prime;
    double md_prime;
    double mh_prime;
    double y_prime;
    double l_init;
    double l_prime;
    double alpha;
    double beta;
    
    mb_walk[0]= drand48();
    md_walk[0]= drand48();
    mh_walk[0]= drand48();
    y_init= funcion(radio,mb_walk[0],md_walk[0],mh_walk[0]);
    l_walk[0]=likelihood(vel_obs,y_init);
    
    int n_interacciones=2000;
        
    }
    
}


