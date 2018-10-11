#include <cstdio>
#include <cstring>


using namespace std;

char encodes[8][1<<8];

// read a char which is not \r or \n
char read_char()
{
  char c;
  while (1)
  {
    c = getchar();
    if (c != '\r' && c != '\n') break;
  }
  return c;
}

int read_encodes()
{
  memset(encodes, 0, sizeof(encodes));
  encodes[1][0] = read_char();
  for (int i = 2; i < 8; i++)
  {
    for (int j = 0; j < (1<<i) - 1; j++)
    {
      char c = getchar();
      if (c == EOF) return 0;
      if ((c == '\n' || c == '\r')) return 1;
      encodes[i][j] = c;
    }
  }
  return 1;
}

int read_int(int len)
{
  int res = 0;
  while (len)
  {
    char c = getchar();
    if (c == '\r' || c == '\n') continue;
    len--;
    res = (res << 1) + (c - '0');
  }
  return res;
}

void print_encodes()
{
  for (int i = 1; i < 8; i++)
  {
    for (int j = 0; j < (1<<i); j++)
    {
      if (encodes[i][j]) printf("%d %d %c\n", i, j, encodes[i][j]);
    }
  }
}

int main()
{
  while (read_encodes())
  {
//    print_encodes();
//    printf("after read encodes\n");
    while (1)
    {
      //    printf("-----wait to read len-----\n");
      int len = read_int(3);
//      printf("len: %d\n", len);
      if (!len) break;
      while (1)
      {
        //      printf("-----wait to read num----\n");
        int num = read_int(len);
        // printf("len: %d, num: %d\n", len, num);
        if (num == (1 << len) - 1) break;
        printf("%c", encodes[len][num]);
      }
    }
    printf("\n");
    
  }
}
