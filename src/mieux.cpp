#include <vector>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <random>
using namespace std;

struct Result {
  vector<int> spins;
  double E0;
  bool degenerate;
};

Result rfim_1d_open(const vector<double>& h,
		    const vector<double>& J){
  const unsigned int L = h.size();
  if (L == 0)
    throw invalid_argument("h ne doit pas être vide");
  if (J.size() != L)
    throw invalid_argument("J doit contenir L elements");
  // Energie minimale avec le dernier spin +1 ou -1
  double Eplus  = -h[0];
  double Eminus = +h[0];
  // Nombre de chemins minimaux.
  // On ne garde que 0, 1 ou 2.
  int nplus  = 1;
  int nminus = 1;
  // Predecesseurs :
  // +1 signifie que le spin precedent etait +1
  // -1 signifie que le spin precedent etait -1
  //  2 signifie que les deux etaient possibles
  vector<int8_t> prev_plus(L);
  vector<int8_t> prev_minus(L);
  for (unsigned int i = 1; i < L; ++i)
    {
      double Ji = J[i - 1];
      // ------------------------------------------------
      // spin_i = +1
      // ------------------------------------------------
      double a = Eplus  - Ji;
      double b = Eminus + Ji;
      double Enew_plus;
      int nnew_plus;
      if (a < b)
        {
	  Enew_plus = -h[i] + a;
	  prev_plus[i] = +1;
	  nnew_plus = nplus;
        }
      else if (b < a)
        {
	  Enew_plus = -h[i] + b;
	  prev_plus[i] = -1;
	  nnew_plus = nminus;
        }
      else
        {
	  Enew_plus = -h[i] + a;
	  prev_plus[i] = 2;
	  nnew_plus = min(2, nplus + nminus);
        }
      // ------------------------------------------------
      // spin_i = -1
      // ------------------------------------------------
      a = Eminus - Ji;
      b = Eplus  + Ji;
      double Enew_minus;
      int nnew_minus;
      if (a < b)
        {
	  Enew_minus = +h[i] + a;
	  prev_minus[i] = -1;
	  nnew_minus = nminus;
        }
      else if (b < a)
        {
	  Enew_minus = +h[i] + b;
	  prev_minus[i] = +1;
	  nnew_minus = nplus;
        }
      else
        {
	  Enew_minus = +h[i] + a;
	  prev_minus[i] = 2;
	  nnew_minus = min(2, nplus + nminus);
        }
      Eplus = Enew_plus;
      Eminus = Enew_minus;
      nplus = nnew_plus;
      nminus = nnew_minus;
    }

  // ----------------------------------------------------
  // Choix du dernier spin
  // ----------------------------------------------------
  int last_spin;
  double E0;
  bool degenerate;
  if (Eplus < Eminus)
    {
      E0 = Eplus;
      last_spin = +1;
      degenerate = (nplus >= 2);
    }
  else if (Eminus < Eplus)
    {
      E0 = Eminus;
      last_spin = -1;
      degenerate = (nminus >= 2);
    }
  else
    {
      E0 = Eplus;
      last_spin = +1;
      degenerate = true;
    }
  // ----------------------------------------------------
  // Reconstruction des spins
  // ----------------------------------------------------
  vector<int> spins(L);
  spins[L - 1] = last_spin;
  for (int i = L - 1; i > 0; --i)
    {
      int p;
      if (spins[i] == +1)
	p = prev_plus[i];
      else
	p = prev_minus[i];
      // Deux predecesseurs possibles :
      // on en choisit arbitrairement un
      if (p == 2)
        {
	  if (spins[i] == +1)
	    p = +1;
	  else
	    p = -1;
        }
      spins[i - 1] = p;
    }
  return {spins, E0, degenerate};
} // FIN Result rfim_1d_open(const vector<double>& h,const vector<double>& J)
// ****************************************************

Result rfim_1d_periodic(const vector<double>& h,
                        const vector<double>& J){
  unsigned int L = h.size();
  if (L < 2)
    throw invalid_argument("Il faut au moins 2 spins");
  if (J.size() != L)
    throw invalid_argument("J doit contenir L elements");

  // ----------------------------------------------------
  // Fonction interne :
  // on impose le premier spin
  // ----------------------------------------------------
  auto solve = [&](int first_spin) -> Result
  {
    double Eplus;
    double Eminus;
    if (first_spin == +1)
      {
	Eplus = -h[0];
	Eminus = numeric_limits<double>::infinity();
      }
    else
      {
	Eplus = numeric_limits<double>::infinity();
	Eminus = +h[0];
      }
    int nplus  = (first_spin == +1) ? 1 : 0;
    int nminus = (first_spin == -1) ? 1 : 0;
    vector<int8_t> prev_plus(L);
    vector<int8_t> prev_minus(L);
    // ------------------------------------------------
    // Dynamique
    // ------------------------------------------------
    for (uint i = 1; i < L; ++i)
      {
	double Ji = J[i - 1];
	// spin_i = +1
	double a = Eplus  - Ji;
	double b = Eminus + Ji;
	double Enew_plus;
	int nnew_plus;
	if (a < b)
	  {
	    Enew_plus = -h[i] + a;
	    prev_plus[i] = +1;
	    nnew_plus = nplus;
	  }
	else if (b < a)
	  {
	    Enew_plus = -h[i] + b;
	    prev_plus[i] = -1;
	    nnew_plus = nminus;
	  }
	else
	  {
	    Enew_plus = -h[i] + a;
	    prev_plus[i] = 2;
	    nnew_plus = min(2, nplus + nminus);
	  }
	// spin_i = -1
	a = Eminus - Ji;
	b = Eplus  + Ji;
	double Enew_minus;
	int nnew_minus;
	if (a < b)
	  {
	    Enew_minus = +h[i] + a;
	    prev_minus[i] = -1;
	    nnew_minus = nminus;
	  }
	else if (b < a)
	  {
	    Enew_minus = +h[i] + b;
	    prev_minus[i] = +1;
	    nnew_minus = nplus;
	  }
	else
	  {
	    Enew_minus = +h[i] + a;
	    prev_minus[i] = 2;
	    nnew_minus = min(2, nplus + nminus);
	  }
	Eplus = Enew_plus;
	Eminus = Enew_minus;
	nplus = nnew_plus;
	nminus = nnew_minus;
      }

    // ------------------------------------------------
    // Ajouter la liaison périodique
    //
    // -J[L-1] s[L-1] s[0]
    // ------------------------------------------------

    double Eplus_periodic =
      Eplus - J[L - 1] * (+1) * first_spin;
    double Eminus_periodic =
      Eminus - J[L - 1] * (-1) * first_spin;
    int last_spin;
    double E0;
    bool degenerate;
    if (Eplus_periodic < Eminus_periodic)
      {
	E0 = Eplus_periodic;
	last_spin = +1;
	degenerate = (nplus >= 2);
      }
    else if (Eminus_periodic < Eplus_periodic)
      {
	E0 = Eminus_periodic;
	last_spin = -1;
	degenerate = (nminus >= 2);
      }
    else
      {
	E0 = Eplus_periodic;
	last_spin = +1;
	degenerate = true;
      }
    // ------------------------------------------------
    // Reconstruction
    // ------------------------------------------------
    vector<int> spins(L);
    spins[L - 1] = last_spin;
    for (int i = L - 1; i > 0; --i)
      {
	int p;
	if (spins[i] == +1)
	  p = prev_plus[i];
	else
	  p = prev_minus[i];
	if (p == 2)
	  {
	    if (spins[i] == +1)
	      p = +1;
	    else
	      p = -1;
	  }
	spins[i - 1] = p;
      }
    return {spins, E0, degenerate};
    // FIN solve
  };

  // ----------------------------------------------------
  // Deux possibilités pour le premier spin
  // ----------------------------------------------------
  Result rplus  = solve(+1);
  Result rminus = solve(-1);
  // ----------------------------------------------------
  // Comparaison
  // ----------------------------------------------------
  if (rplus.E0 < rminus.E0)
    return rplus;
  if (rminus.E0 < rplus.E0)
    return rminus;
  // Les deux ont des premiers spins différents :
  // ce sont donc deux configurations distinctes.
  rplus.degenerate = true;
  return rplus;
} // FIN Result rfim_1d_periodic(const vector<double>& h,vector<double>& J)
// ***********************************************************************

Result rfim_1d(const vector<double>& h,const vector<double>& J) {
  unsigned int L = J.size();
  if (J[L-1]==0)
    return rfim_1d_open(h,J);
  return rfim_1d_periodic(h,J);
}   // FIN Result rfim_1dconst vector<double>& h,const vector<double>& J)
// ********************************************************************

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
