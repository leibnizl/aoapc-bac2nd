#define LOCAL
#include <cstdio>
#include <cstring>
#include <iostream>

int n, m;
int horizontal[13][13], vertical[13][13];

bool get_cube(int x, int y, int len)
{
  if (x + len > n || y + len > n) return false;
  for (int i = 0; i < len; i++)
  {
    if(!horizontal[x][y+i]) return false;
    if(!vertical[x+i][y]) return false;
    if(!horizontal[x+len][y+i]) return false;
    if(!vertical[x+i][y+len]) return false;
  }
  return true;
}

int get_cube(int len)
{
  int res = 0;
  for (int i = 1; i < n; i++)
  {
    for (int j = 1; j < n; j++)
    {
      if(get_cube(i, j, len)) res++;
    }
  }
  return res;
}

int main()
{
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  int kase = 0;
  while (scanf("%d%d", &n, &m) == 2)
  {
    if (kase++) printf("\n**********************************\n\n");
    printf("Problem #%d\n\n", kase);
    memset(horizontal, 0, sizeof(horizontal));
    memset(vertical, 0, sizeof(vertical));
    for (int i = 0; i < m; i++)
    {
      char c;
      int x, y;
      std::cin >> c >> x >> y;
      if (c == 'H')
      {
        horizontal[x][y] = 1;
      }
      else
      {
        vertical[y][x] = 1;
      }
    }
    bool flag = true;
    for (int i = 1; i < n; i++)
    {
      int cnt = get_cube(i);
      if (cnt)
      {
        printf("%d square (s) of size %d\n", cnt, i);
        flag = false;
      }
    }
    if (flag) printf("No completed squares can be found.\n");
  }
}
