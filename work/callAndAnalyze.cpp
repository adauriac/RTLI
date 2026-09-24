#include <vector>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <random>

using namespace std;
#include <macros.h>
#include <jc.h>
#define _COMMENTS "RFIM 1d\n"

#include "RFIM1d.h"

struct Properties {
  double M;
  double E;
  double Correl;
};

struct Stat {
  double moy;
  double moydeabs;
  double moydecarre;
  double mi;
  double ma;
  unsigned int size;
};

Stat anaVect(vector<double>&V);
void analyse(const Result &res,Properties &prop) ;
void out(const vector<double>& h,const vector<double>& J,const Result &res);
void readFromFile(char*fileName,vector<double>&hs,vector<double>&Js);

Stat anaVect(vector<double>&V){
  Stat result;
  result.moy = 0;
  result.moydeabs = 0;
  result.moydecarre = 0;
  result.mi = 1e100;
  result.ma = -1e100;
  result.size = V.size();
  for (unsigned int i=0;i<V.size();i++) {
   result.moy += V[i];
   result.moydeabs += V[i]>0 ? V[i] : -V[i];
   result.moydecarre += V[i]*V[i];
   if (V[i]<result.mi)
     result.mi = V[i];
   if (V[i]>result.ma)
     result.ma = V[i];
  result.size = V.size();
  }
  result.moy /= V.size();
  result.moydeabs /= V.size();
  result.moydecarre /= V.size();
  return result;
}   // FIN Stat anaVect(vector<double>&V){
// ***********************************************************************************

void readFromFile(char*fileName,vector<double>&hs,vector<double>&Js) {
  hs.resize(0);
  Js.resize(0);
  FILE *ft;
  _OUVREFILE(fileName,ft,"r");
  for(;;) {
    char line[256];
    if (fgets(line,255,ft)==NULL)
      break;
    if (line[0]=='#')
      continue;
    double h,J;
    if (sscanf(line,"%lf %lf",&h,&J)!=2)
      _STOP("syntax error : %s ",line);
    hs.push_back(h);
    Js.push_back(J);
  }
} // FIN void readFromFile(char*fileName,vector<double>&hs,vector<double>&Js)
// *********************************************************************

void out(const vector<double>& h,const vector<double>& J,const Result &res){
  unsigned int L=h.size();
  unsigned int l = ( L>=16 ? 16 : L);
  const char *end= (L!=l) ? " ...\n" : "\n";
  printf("E0= %lf\n",res.E0/L);
  printf("h: ");
  for (uint i=0;i<l;i++)
    printf("%lf ",h[i]);
  printf("%s",end);
  printf("J: ");
  for (uint i=0;i<l;i++)
    printf("%lf ",J[i]);
  printf("%s",end);
  printf("spin s: ");
  for (uint i=0;i<l;i++)
    printf("%c",res.spins[i]==1 ? '+' : '-');
  printf("%s",end);
}  // FIN void out( vector<double>& h, vector<double>& J, Result &res){
// ****************************************************************

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
void helper() {
  printf("\n");
  printf("\t\tTrouve le GS d'un RFIM 1d\n");
  printf("Les donnees peuvent etre générées ou lues dans un fichier.\n");
  printf("Elles sont lues dans un fichier si le paramètre fileName est affecté au nom du fichier (chaine de caractères)\n");
  printf("Les lignes commencant par # sont des commentaires, sinon deux valeurs h et J par ligne.\n");
  printf("Sinon elles sont générées avec les paramètres L, H, periodic, seed, nCalls \n");
  printf("Les Js sont uniforme dans [0,1], les Hs uniformmes dans [-H,H]\n");
  printf("nCalls est le nombre samples générés\n");
  printf("Les résultats E0,M,<|s_{x}*s_{x+L/2}|> sont affichés sur stdout avec les paramètres de ce runs\n");
  printf("Si verbose>=1 les Js,hs, spins sont affichés\n");
  printf("\n");
}
// *********************************************************************
//                      EN AVANT SIMONE
// *********************************************************************
int main(int na,char*para[]) {
  _INITQ;
  int verbose = 1;
  unsigned int L = 8;
  unsigned int seed = 51154;
  unsigned nCalls = 1;
  double H = 10;
  unsigned int per = 0;
  char fileName[256] = "";
  for (int i=1;i<=na;i++)
    {
      char *st,noml[255],ok,j;
     
      st = para[i];
      ok = i==na;
      if (!ok)
        cmdline+=string(st)+" ";
      
      for (j=0;j<2;j++)
	{
	  if (j && !ok) 
	    {
	      printf(_COMMENTS);
	      printf("usage (%s):\n",st);
	    }
	  // METTRE ICI LES DIFFERNTES VALEURS DE LA LIGNE DE COMMANDE
	  _QU(verbose,"%d"," (niveau de blabla)");
	  _QU(L,"%u"," (Taille chaine)");
	  _QU(seed,"%u"," (amorceur rnd)");
	  _QU(nCalls,"%u"," (nombre de samples générés)");
	  _QU(per,"%u"," (periodique ou non");
	  _QU(H,"%lf"," (distibution des champs = [-H,H])");
	  _QUS(fileName,"%s"," (read data in filename, all aother parameters except verbose not considered)");
	}
      if (!ok) 
	{
          helper();
          exit(0);
        }
    }
  vector<double> hs(L),Js(L);
  if (fileName[0]!=0) {
    readFromFile(fileName,hs,Js);
    nCalls =1;
  }
  random_device rd;
  if (seed==0)
    seed= rd();
  mt19937_64 rng; 
  uniform_real_distribution<double> disth(-H, H);
  uniform_real_distribution<double> distJ(0, 1.0);
  vector<double> lesE,lesM,lesC;
  for(unsigned int k=0;k<nCalls;k++) {
    rng.seed(seed);
    if (fileName[0]==0) {
      for (unsigned int i=0;i<L;i++) {
	hs[i] = disth(rng);
	Js[i] = distJ(rng);
      }
      if (!per)
	Js[Js.size()-1] = 0.;
    }
    Result res= rfim_1d(hs,Js);
    if (verbose)
      out(hs,Js,res);
    Properties prop;
    analyse(res,prop);
    // fprintf(stdout,"L= %u H= %lf E= %lf M= %lf C= %lf seed= %u\n",L,H,prop.E,prop.M,prop.Correl,seed);
    // fflush(stdout);
    lesE.push_back(prop.E);
    lesM.push_back(prop.M);
    lesC.push_back(prop.Correl);
    seed = rng(); // pour le prochain appel
  } // fin loop samples
  // here one plays with the results
  printf("\nL= %u H= %lf\n",L,H);
  Stat s = anaVect(lesE);
  printf("E: <>=%lf <||>=%lf <**2>=%lf min=%lf max=%lf nb=%d\n",s.moy , s.moydeabs, s.moydecarre, s.mi, s.ma, s.size);
  s = anaVect(lesM);
  printf("M: <>=%lf <||>=%lf <**2>=%lf min=%lf max=%lf nb=%d\n",s.moy , s.moydeabs, s.moydecarre, s.mi, s.ma, s.size);
  s = anaVect(lesC);
  printf("C: <>=%lf <||>=%lf <**2>=%lf min=%lf max=%lf nb=%d\n",s.moy , s.moydeabs, s.moydecarre, s.mi, s.ma, s.size);
  return 0;
}  // FIN
// *******************************************************************
