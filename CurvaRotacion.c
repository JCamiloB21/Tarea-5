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
double radio[301];
double vel_obs[301];
double likelihood(double hola[300], double vel_model[300]);
double funcion(double chao[300],double mb, double md, double mh);
void caminata();
double randn (double mu, double sigma);

int main(void){
   
    double vel_model[300];
    double mb;
    double md;
    double mh;
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
    likelihood(vel_obs,vel_model);
    caminata();
}
double likelihood(double hola[300],double vel_model[300]){
    double suma=0;
    for(i=0;i<301;i++){
        suma= suma + pow((hola[i]-vel_model[i]),2);
    }
    double chi=(1.0/2.0)*suma;
    return exp(-chi);
}

double funcion(double chao[300],double mb, double md, double mh){
    double vel;
    double a;
    double b;
    double c;
    for(i=0;i<301;i++){
        a=(sqrt(mb)*chao[i])/pow((chao[i]*chao[i] + bb*bb),3/4);
        b=(sqrt(md)*chao[i])/pow((chao[i]*chao[i] + ((bd+ad)*(bd+ad))),3/4);
        c=sqrt(mh)/pow((chao[i]*chao[i] + ah*ah),1/4);
        vel= a + b + c;
    }
    return vel;
}
double randn (double mu, double sigma)
{
  double U1, U2, W, mult;
  static double X1, X2;
  static int call = 0;
 
  if (call == 1)
    {
      call = !call;
      return (mu + sigma * (double) X2);
    }
 
  do
    {
      U1 = -1 + ((double) rand () / RAND_MAX) * 2;
      U2 = -1 + ((double) rand () / RAND_MAX) * 2;
      W = pow (U1, 2) + pow (U2, 2);
    }
  while (W >= 1 || W == 0);
 
  mult = sqrt ((-2 * log (W)) / W);
  X1 = U1 * mult;
  X2 = U2 * mult;
 
  call = !call;
 
  return (mu + sigma * (double) X1);
}
/*el metodo gaussiano se tomo de la pagina https://phoxis.org/2013/05/04/generating-random-numbers-from-normal-distribution-in-c/*/
void caminata(){
    int n_interacciones=2000;
    double suma=0;
    double *y_init=malloc(n_interacciones*sizeof(double));
    double mb_prime;
    double md_prime;
    double mh_prime;
    double *y_prime=malloc(n_interacciones*sizeof(double));
    double *l_walk=malloc(n_interacciones*sizeof(double));
    double *mb_walk=malloc(n_interacciones*sizeof(double));
    double *md_walk=malloc(n_interacciones*sizeof(double));
    double *mh_walk=malloc(n_interacciones*sizeof(double));
    double l_init;
    double l_prime;
    double alpha;
    double beta;
    double max_like;
    
    mb_walk[0]= drand48();
    md_walk[0]= drand48();
    mh_walk[0]= drand48();
    y_init[i]= funcion(radio,mb_walk[0],md_walk[0],mh_walk[0]);
    l_walk[0]=likelihood(vel_obs,y_init);
    for(i=1;i<n_interacciones;i++){
        mb_prime=randn(mb_walk[i], 0.1);
        md_prime=randn(md_walk[i], 0.1);
        mh_prime=randn(mh_walk[i], 0.1); 
        
        y_init[i] = funcion(radio,mb_walk[i],md_walk[i],mh_walk[i]);
        y_prime[i] = funcion(radio, mb_prime, md_prime, mh_prime);
        
        l_prime = likelihood(vel_obs, y_prime);
        l_init = likelihood(vel_obs, y_init);
        
        alpha = l_prime/l_init;
        if(alpha>=1.0){
            mb_walk[i+1]= mb_prime;
            md_walk[i+1]= md_prime;
            mh_walk[i+1]= mh_prime; 
            l_walk[i+1]=l_prime;
        }else{
            beta=drand48();
            if(beta<=alpha){
                mb_walk[i+1]= mb_prime;
                md_walk[i+1]= md_prime;
                mh_walk[i+1]= mh_prime; 
                l_walk[i+1]=l_prime;

            }else{
                mb_walk[i]= mb_walk[i];
                md_walk[i]= mb_walk[i];
                mh_walk[i]= mb_walk[i]; 
                l_walk[i]= l_init;
            }  
        }
    }
    int max=0;
    double val_max=0;
    double mejor_mb;
    double mejor_md;
    double mejor_mh;
    for(i=0;i<2000;i++){
        if(l_walk[i]>val_max){
            val_max=l_walk[i];
            max=i;
        }
    }
    max_like=max;
    mejor_mb=mb_walk[max];
    mejor_md=md_walk[max];
    mejor_mh=mh_walk[max];
    
    printf("%lf\n",mejor_mb);
    printf("%lf\n",mejor_md);
    printf("%lf\n",mejor_mh);
}


