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
double radio[301];
double vel_obs[301];
double chi;
int i;
double sqrt(double x);


float likelihood(double velocidad,double vel_model);


int main(void){
    FILE *in;
    int i;
    double var1;
    double var2;
    int test;
    char filename[150]="RadialVelocities.dat";
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
}
float likelihood(double velocidad,double vel_model){
    double suma=0;
    for(i=0;i<301;i++){
        suma= suma + (velocidad-vel_model)*(velocidad-vel_model);
    }
    double chi=(1.0/2.0)*suma;
    return exp(-chi);
}

float funcion(float rad,float mb, float md, float mh){
    return (sqrt(mb)*rad)/pow((rad*rad + bb*bb),3/4) + (sqrt(md)*rad)/pow((rad*rad + ((bd+ad)*(bd+ad))),3/4) + (sqrt(mh))/pow((rad*rad + ah*ah),3/4);
}



