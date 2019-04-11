#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <ctime>

using namespace std;
 
vector <double> leer(string filename);
vector <double> modelo(vector <double> x, vector <double> c);
double loglike(vector <double> x, vector <double> y, vector <double> c);
void MCMC_polynomial(vector <double> x_obs, vector <double> y_obs, int n_steps, int poly_degree);
double min(double x, double y);

int main () {
  string filename;
  string filename1;   
  vector<double> valores_x;
  vector<double> valores_y;  
  filename="valores_x.txt";
  filename1="valores_y.txt";  
  valores_x=leer(filename);
  valores_y=leer(filename1); 
  MCMC_polynomial(valores_x, valores_y, 1000000, 3);   
  return 0;
}

vector <double> leer(string filename){
  ifstream infile; 
  string line;
  string lect; 
  vector<double> val_x;  
  infile.open(filename); 
  getline(infile, line);
  while(infile){ 
   lect=lect+line+" ";
   val_x.push_back(atof(line.c_str()));   
   getline(infile, line);
  } 
  infile.close();
  return val_x;  
}

vector <double> modelo(vector <double> x, vector <double> c){
    vector <double> rta;
    double resp;
    int n=x.size();
    int m=c.size();
    int i;
    int j;
    for (i=0;i<n;i++){
        resp=0;
        for(j=0;j<m;j++){
            resp+=c[j]*pow(x[i],j);}
        rta.push_back(resp);
    }
    return rta;
}

double loglike(vector <double> x, vector <double> y, vector <double> c){
    double d1;
    double suma=0.0;
    int i=0;
    int n=x.size();
    for (i=0;i<n;i++){
        d1=y[i]-modelo(x,c)[i];
        d1=d1/0.1;
        d1=d1*d1;
        suma+=d1;}
    suma=-0.5*suma;   
    return suma;
}

double min(double x, double y){
double r;
    if (x<y){
        r=x;}
    else{
        r=y;}
return y;    
}

void MCMC_polynomial(vector <double> x_obs, vector <double> y_obs, int n_steps, int poly_degree){
  srand48(time(0));
  vector<double> coef;
  vector<double> logp;
  int i;
  for (i=0;i< poly_degree+1;i++){
      coef.push_back(0);}
  
  logp.push_back(loglike(x_obs,y_obs, coef));
  
  int k;
  string envio;
  for (k=0; k< poly_degree+1;k++){
      envio+=to_string(coef[k])+" ";}
  cout<<envio<<endl;            
 
  int j;
  
  double logposterior_viejo;
  double logposterior_nuevo;
  double r;  
  double alpha;  
  for (j=1;j<n_steps;j++){
      vector<double> prop;
      prop.resize(poly_degree+1);
      int l;
      for (l=0;l< poly_degree+1;l++){
      prop[l]=coef[l]+0.2*drand48()-0.1;}
      
      logposterior_viejo = loglike(x_obs,y_obs, coef); 
     logposterior_nuevo = loglike(x_obs,y_obs, prop) ;
      r = min(1.0,exp(logposterior_nuevo-logposterior_viejo));
    alpha = drand48();
    if(alpha<r){
        int m;
        for (m=0;m< poly_degree+1;m++){
      coef[m]=prop[m];}
        logp.push_back(logposterior_nuevo);}
    else{
        logp.push_back(logposterior_viejo);}
     string send;
     int n;
  for (n=0; n< poly_degree+1;n++){
      send+=to_string(coef[n])+" ";}
  cout<<send<<endl;    
  }
  
}
