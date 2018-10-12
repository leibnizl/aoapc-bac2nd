#define LOCAL
#include <cstdio>
#include <cstring>
#include <iostream>

// 用二位数组来保存图，且约定：0表示空，1为帅，2为车，3为马，4为炮
int map_xiangqi[13][13];


bool is_valid_jiang_pos(int x, int y)
{
  return (x > 0) && (x < 4) && (y > 3) && (y < 7);
}
// 检查帅和车是否可能造成将军
bool checkR(int x, int y)
{
  for (int i = x - 1; i > 0; i--)
  {
    if (map_xiangqi[i][y] == 2) return true;
    else if (map_xiangqi[i][y]) break;
  }
  for (int i = x + 1; i < 13; i++)
  {
    if (map_xiangqi[i][y] == 1 || map_xiangqi[i][y] == 2) return true;
    else if (map_xiangqi[i][y]) break;
  }
  for (int i = y - 1; i > 0; i--)
  {
    if (map_xiangqi[x][i] == 2) return true;
    else if (map_xiangqi[x][i]) break;
  }
  for (int i = y + 1; i < 13; i++)
  {
    if (map_xiangqi[x][i] == 2) return true;
    else if (map_xiangqi[x][i]) break;
  }
  return false;
}

bool checkC(int x, int y)
{
  int cnt = 0;
  for (int i = x - 1; i > 0; i--)
  {
    if (map_xiangqi[i][y])
    {
      cnt++;
      if (map_xiangqi[i][y] == 4 && cnt == 2) return true;
    }
  }
  cnt = 0;
  for (int i = x + 1; i < 13; i++)
  {
    if (map_xiangqi[i][y])
    {
      cnt++;
      if (map_xiangqi[i][y] == 4 && cnt == 2) return true;
    }
  }
  cnt = 0;
  for (int i = y - 1; i > 0; i--)
  {
    if (map_xiangqi[x][i])
    {
      cnt ++;
      if (map_xiangqi[x][i] == 4 && cnt == 2) return true;
    }
    
  }
  cnt = 0;
  for (int i = y + 1; i < 13; i++)
  {
    if (map_xiangqi[x][i])
    {
      cnt++;
      if (map_xiangqi[x][i] == 4 && cnt == 2) return true;
    }

  }
  return false;
}

bool is_valid_pos(int x, int y)
{
  return (x < 11) && (x > 0) && (y < 10) && (y > 0);
}

bool checkH(int x, int y)
{
  bool pos1 = is_valid_pos(x - 1, y - 2) && map_xiangqi[x - 1][y - 2] == 3 && !map_xiangqi[x - 1][y - 1];
  bool pos2 = is_valid_pos(x - 2, y - 1) && map_xiangqi[x - 2][y - 1] == 3 && !map_xiangqi[x - 1][y - 1];
  bool pos3 = is_valid_pos(x - 2, y + 1) && map_xiangqi[x - 2][y + 1] == 3 && !map_xiangqi[x - 1][y + 1];
  bool pos4 = is_valid_pos(x - 1, y + 2) && map_xiangqi[x - 1][y + 2] == 3 && !map_xiangqi[x - 1][y + 1];
  bool pos5 = is_valid_pos(x + 1, y + 2) && map_xiangqi[x + 1][y + 2] == 3 && !map_xiangqi[x + 1][y + 1];
  bool pos6 = is_valid_pos(x + 2, y + 1) && map_xiangqi[x + 2][y + 1] == 3 && !map_xiangqi[x + 1][y + 1];
  bool pos7 = is_valid_pos(x + 2, y - 1) && map_xiangqi[x + 2][y - 1] == 3 && !map_xiangqi[x + 1][y - 1];
  bool pos8 = is_valid_pos(x + 1, y - 2) && map_xiangqi[x + 1][y - 2] == 3 && !map_xiangqi[x + 1][y - 1];
  return pos1 || pos2 || pos3 || pos4 || pos5 || pos6 || pos7 || pos8;
}

bool is_checked(int x, int y)
{
  return !is_valid_jiang_pos(x, y) || checkR(x, y) || checkH(x, y) || checkC(x, y);
}

int main()
{
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  
  int n,jiangx, jiangy;
  int cnt = 0;
  while (scanf("%d%d%d", &n, &jiangx, &jiangy) == 3 && n)
  {
//    std::cout << cnt++ << std::endl;
    memset(map_xiangqi, 0, sizeof(map_xiangqi));
    for (int i = 0; i < n; i++)
    {
      char c;
      int x, y;
      //  scanf("%c%d%d", &c, &x, &y);
      std:: cin >> c >> x >> y;
      switch (c) {
      case 'G':
        map_xiangqi[x][y] = 1;
        break;
      case 'R':
        map_xiangqi[x][y] = 2;
        break;
      case 'H':
        map_xiangqi[x][y] = 3;
        break;
      case 'C':
        map_xiangqi[x][y] = 4;
      }
      
    }
    if (is_checked(jiangx - 1, jiangy) && is_checked(jiangx + 1, jiangy) && is_checked(jiangx, jiangy - 1) && is_checked(jiangx, jiangy + 1))
      printf("YES\n");
    else printf("NO\n");
  }
}
