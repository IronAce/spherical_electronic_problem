#include <iostream>
#include <complex>
#include <cmath>
#include "math.h"

using namespace std;
typedef complex<double> dcomp;

main() {
  dcomp i;
  dcomp a;
  double pi;
  pi = 2 * asin(1);
  i = -1;
  i = sqrt(i);
  a = exp(2*pi*i);
  cout << "i is " << i << "and Euler was right: e(i pi) = " << a << endl;
}
