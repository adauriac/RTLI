#include <vector>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <random>

#include "RFIM1d.h"

struct Properties {
  double M;
  double E;
  double Correl;
};
void analyse(const Result &res,Properties &prop) ;

void analyse(const Result &res,Properties &prop) {
  double M = 0,C = 0;
  unsigned int L = res.spins.size();
  for (unsigned int i=0;i<L;i++) 
    M += res.spins[i];
  M /= L;
  for (unsigned int i=0;i<L/2;i++) 
    C += res.spins[i]*res.spins[(i+L/2)%L];
  C /= L/2;
  prop.E = res.E0/L;
  prop.M = M;
  prop.Correl = C;
} // FIN void analyse(const Results &res,const Properties &prop) 
// ****************************************************************

// *********************************************************************
//                      EN AVANT SIMONE
// *********************************************************************
int main(int na,char*argv[]) {
  // Reading the parameters
  if (na != 5) {
    printf("syntax: %s L H seed (0 automatic choice) ncall\nncall calls\n",argv[0]);
    exit(1);
  }
  unsigned int L,seed,nCalls;
  double H;
  if (sscanf(argv[1],"%u",&L)!=1)
    exit(2);
  if (sscanf(argv[2],"%lf",&H)!=1)
    exit(3);
  if (sscanf(argv[3],"%u",&seed)!=1)
    exit(4);
  if (sscanf(argv[4],"%u",&nCalls)!=1)
    exit(4);
  vector<double> hs(L),Js(L);
  random_device rd;
  if (seed==0)
    seed= rd();
  mt19937_64 rng; 
  uniform_real_distribution<double> disth(-H, H);
  uniform_real_distribution<double> distJ(0, 1.0);
  
  for(unsigned int k=0;k<nCalls;k++) {
    rng.seed(seed);
    for (unsigned int i=0;i<L;i++) {
      hs[i] = disth(rng);
      Js[i] = distJ(rng);
    }
    if (L<=10) {
      printf("h: ");
      for (uint i=0;i<L;i++)
	printf("%lf ",hs[i]);
      printf("\nJ: ");
      for (uint i=0;i<L;i++)
	printf("%lf ",Js[i]);
      printf("\n");
    }
  
    Result res= rfim_1d(hs,Js);
    Properties prop;
    analyse(res,prop);
    fprintf(stdout,"L= %u H= %lf E= %lf M= %lf C= %lf seed= %u\n",L,H,prop.E,prop.M,prop.Correl,seed);
    fflush(stdout);
    seed = rng(); // pour le prochain appel
  } // fin loop samples
  return 0;
}  // FIN
// *******************************************************************
