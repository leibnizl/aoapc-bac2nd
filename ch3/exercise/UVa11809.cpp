#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;

int main()
{
  double tmp[11][31];
  double t = 1.0;
  double M = 0.0;
  double E;
  // get number from i and j , number = M * 2 ^ E
  // calculate M from i, and calculate E from j
  // since number may overflow, so use log to calculate
  // log(number) = log(M) + Elog(2)
  for (int i = 0; i < 10; i++)
  {
    t /= 2;
    M += t;
    for (int j = 1; j < 31; j++)
    {
      E = (1 << j) - 1;
      tmp[i][j] = log10(M) + E * log10(2);
    }
  }
  char in[20];
  while (scanf("%s", in))
  {
    if (strlen(in) == 3) break;
    char A[18], B[40];
    strncpy(A, in, 17);
    A[17] = 0;
    strcpy(B, in+18);
    double a = atof(A), b = atof(B);
    double loga = log10(a);

    bool flag = false;
    for (int i = 0; i < 10; i++)
    {
      for (int j = 1; j < 31; j++)
      {
        if (fabs(tmp[i][j] - loga - b) < 0.000001)
        {
          printf("%d %d\n", i, j);
          flag = true;
          break;
        }
      }
      if (flag) break;
    }
  }
}
