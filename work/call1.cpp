#include <vector>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <random>

#include "RFIM1d.h"

// *********************************************************************
//                      EN AVANT SIMONE
// *********************************************************************
int main(int na,char*para[]) {
  unsigned int L;
  vector<double> hs,Js;
  if (na==3) {
    unsigned int seed;
    sscanf(para[1],"%u",&L);
    sscanf(para[2],"%u",&seed);
    mt19937_64 rng(seed);  // graine
    uniform_real_distribution<double> disth(-1.0, 1.0);
    uniform_real_distribution<double> distJ(-0, 1.0);
    hs.resize(L);
    Js.resize(L);
    for (uint i=0;i<L;i++) {
      hs[i] = disth(rng);
      Js[i] = distJ(rng);
    }
    Js[L-1] = 0;
  } else {
    FILE *ft=fopen("dataTest","r");
    for(;;) {
      char line[128];
      double h,J;
      if (fgets(line,127,ft)==NULL)
	break;
      sscanf(line,"%lf %lf",&h,&J);
      Js.push_back(J);
      hs.push_back(h);
    }
    fclose(ft);
    L= hs.size();
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
  printf("E0= %lf\n",res.E0);
  if (L<=10) {
    for (uint i=0;i<L;i++)
      printf("%d ",res.spins[i]);
    printf("\n");
  }
  return 0;
}  // FIN
// *******************************************************************
