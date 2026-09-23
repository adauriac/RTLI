using namespace std;

struct Result {
  vector<int> spins;
  double E0;
  bool degenerate;
};

Result rfim_1d(const vector<double>& h,const vector<double>& J);
