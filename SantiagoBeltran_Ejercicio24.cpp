#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;
 
vector <double> leer(string filename);
vector <double> modelo(vector <double> x, double a, double b, double c, double d);
double loglike(vector <double> x, vector <double> y, double a, double b, double c, double d);
double min(double x, double y);
double prom(vector<double> valores);

int main () {
  string filename;
  string filename1;   
  vector<double> valores_x;
  vector<double> valores_y;  
  filename="valores_x.txt";
  filename1="valores_y.txt";  
  valores_x=leer(filename);
  valores_y=leer(filename1); 
  srand48(23);
  int N=50000;
  vector<double> a;
  vector<double> b;
  vector<double> c;
  vector<double> d;
  vector<double> logp;
  a.push_back(drand48());
  b.push_back(drand48());
  c.push_back(drand48());
  d.push_back(drand48());
  logp.push_back(loglike(valores_x,valores_y, a[0],b[0],c[0],d[0])); 
  double sigma_delta_a = 0.2;
double sigma_delta_b = 0.2;
double sigma_delta_c = 0.2;
double sigma_delta_d = 0.2;    
  int j;
  double p_a; 
  double p_b; 
  double p_c; 
  double p_d;
  double logposterior_viejo;
  double logposterior_nuevo;
  double r;  
  double alpha;  
  for (j=1;j<N;j++){
      p_a=a[j-1]+2*drand48()-1;
      p_b=b[j-1]+2*drand48()-1;
      p_c=c[j-1]+2*drand48()-1;
      p_d=d[j-1]+2*drand48()-1;
      logposterior_viejo = loglike(valores_x, valores_y, a[j-1], b[j-1], c[j-1], d[j-1]); 
     logposterior_nuevo = loglike(valores_x, valores_y, p_a, p_b, p_c,p_d) ;
      r = min(1.0,exp(logposterior_nuevo-logposterior_viejo));
    alpha = drand48();
    if(alpha<r){
        a.push_back(p_a);
        b.push_back(p_b);
        c.push_back(p_c);
        d.push_back(p_d);
        logp.push_back(logposterior_nuevo);}
    else{
        a.push_back(a[j-1]);
        b.push_back(b[j-1]);
        c.push_back(c[j-1]);
        d.push_back(d[j-1]);
        logp.push_back(logposterior_viejo);}
  }
  double a_prom; 
  double b_prom; 
  double c_prom; 
  double d_prom;
  a_prom=prom(a);
  b_prom=prom(b);
  c_prom=prom(c);
  d_prom=prom(d);
  cout<<a_prom<<endl;
    cout<<b_prom<<endl;
    cout<<c_prom<<endl;
    cout<<d_prom<<endl;  
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

vector <double> modelo(vector <double> x, double a, double b, double c, double d){
    vector <double> rta;
    double resp;
    int n=x.size();
    int i;
    for (i=0;i<n;i++){
        resp=a+b*x[i]+c*x[i]*x[i]+d*x[i]*x[i]*x[i];
        rta.push_back(resp);
    }
    return rta;
}

double loglike(vector <double> x, vector <double> y, double a, double b, double c, double d){
    double d1;
    double suma=0.0;
    int i=0;
    int n=x.size();
    for (i=0;i<n;i++){
        d1=y[i]-modelo(x,a,b,c,d)[i];
        d1=d1/0.00001;
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


double prom(vector<double> valores){
 double suma=0;
 int i;   
 for(i=0; i<valores.size();i++){
     suma+=valores[i];}
 suma=suma/(valores.size());
 return suma;   
}    

