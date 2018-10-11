#define LOCAL
#include <cstdio>

using namespace std;

const int maxd = 10000;
int r, c, n, kase = 0;

struct Command{
  char c[5];
  int r1, c1, r2, c2;
  int a, x[20];
}cmd[maxd];

int simulate(int &qr, int &qc)
{
  for (int i = 0; i < n; i++)
  {

    int cnt = 0;
    int cmp = cmd[i].c[1] == 'R' ? qr : qc;
    if (cmd[i].c[0] == 'E')
    {
      if (cmd[i].r1 == qr && cmd[i].c1 == qc)
      {
        qr = cmd[i].r2;
        qc = cmd[i].c2;
      }
      else if (cmd[i].r2 == qr && cmd[i].c2 == qc)
      {
        qr = cmd[i].r1;
        qc = cmd[i].c1;
      }
      continue;
    }
    if (cmd[i].c[0] == 'D')
    {
      for (int j = 0; j < cmd[i].a; j++)
      {
        if (cmd[i].x[j] == cmp) return 0;
        else if (cmd[i].x[j] < cmp) cnt--;
      }
      
    }
    else
    {
      for (int j = 0; j < cmd[i].a; j++)
      {
        if (cmd[i].x[j] <= cmp) cnt++;
      }
    }
    cmd[i].c[1] == 'R' ? qr += cnt : qc += cnt; 
  }
  return 1;
}

int main()
{
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  
  while (scanf("%d%d%d", &r, &c, &n) == 3 && r)
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%s", cmd[i].c);
      if (cmd[i].c[0] == 'E')
      {
        scanf("%d%d%d%d", &cmd[i].r1, &cmd[i].c1, &cmd[i].r2, &cmd[i].c2);
      }
      else
      {
        scanf("%d", &cmd[i].a);
        for (int j = 0; j < cmd[i].a; j++)
        {
          scanf("%d", &cmd[i].x[j]);
        }
      }
    }
    int q, qr, qc;
    scanf("%d", &q);
    if (kase) printf("\n");
    printf("Spreadsheet #%d\n", ++kase);
    
    while(q--)
    {
      scanf("%d%d", &qr, &qc);
      printf("Cell data in (%d,%d) ", qr, qc);
      
      if (!simulate(qr, qc))
      {
        printf("GONE\n");
      }
      else
      {
        printf("moved to (%d,%d)\n", qr, qc);
      }
    }
  }
}
