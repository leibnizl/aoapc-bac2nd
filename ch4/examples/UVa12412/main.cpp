#define LOCAL
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxd = 1000007;
const int maxl = 17;
int stu_num;
struct Student{
  int CID;
  char name[maxl], SID[maxl];
  int chinese, math, english, programming, sum;
  double average;
  bool removed;
}students[maxd];

void print_menu()
{
  printf("Welcome to Student Performance Management System (SPMS).\n\n");
  printf("1 - Add\n");
  printf("2 - Remove\n");
  printf("3 - Query\n");
  printf("4 - Show ranking\n");
  printf("5 - Show Statistics\n");
  printf("0 - Exit\n\n");
}

void add()
{
  printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
  char sid[maxl];
  while (scanf("%s", sid) && strlen(sid) != 1)
  {
    bool duplicated = false;
    for (int i = 0; i < stu_num; i++)
    {
      if (!students[i].removed && !strcmp(students[i].SID, sid))
      {
        duplicated = true;
        break;
      }
    }
    strcpy(students[stu_num].SID, sid);
    
    scanf("%d%s%d%d%d%d", &students[stu_num].CID, students[stu_num].name, &students[stu_num].chinese, &students[stu_num].math, &students[stu_num].english, &students[stu_num].programming);
    students[stu_num].sum = students[stu_num].chinese + students[stu_num].math + students[stu_num].english + students[stu_num].programming;
    students[stu_num].average = students[stu_num].sum * 1.0 / 4 + 1e-6;
//    cout << "add student " << stu_num << ", name: " << students[stu_num].name << ", chinese" << students[stu_num].chinese << ",sum: " << students[stu_num].sum << ", average: " << students[stu_num].average << endl;
    if (duplicated)
    {
      printf("Duplicated SID.\n");
    }
    else stu_num++;
    printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
  }
}

int get_rank(int t)
{
  int cnt = 0;
  for (int i = 0; i < stu_num; i++)
  {
    if (!students[i].removed && students[i].sum > students[t].sum) cnt++;
  }
  return cnt + 1;
}



void DQ(int is_query)
{
  char sid[maxl];
  
  while (1)
  {
    printf("Please enter SID or name. Enter 0 to finish.\n");
  
    scanf("%s", sid);
    if (strlen(sid) == 1) break;
    int rm_cnt = 0;
    for (int i = 0; i < stu_num; i++)
    {
      if (students[i].removed) continue;
      if (!strcmp(students[i].SID, sid) || !strcmp(students[i].name, sid))
      {
        if (is_query)
        {
          printf("%d %s %d %s %d %d %d %d %d %.2f\n", get_rank(i), students[i].SID, students[i].CID, students[i].name, students[i].chinese, students[i].math, students[i].english, students[i].programming, students[i].sum, students[i].average);
        }
        else
        {
          students[i].removed = true;
          rm_cnt++;
        }
      }
    }
    if (!is_query) printf("%d student(s) removed.\n", rm_cnt);
  }

}

struct Statistics{
  // 0: passed, 1: failed, 2: scores sum.
  int chinese[3], math[3], english[3], programming[3];
  int cnt;
  // 0: passed 0 subjects, ... , 4: passed 4 subjects;
  int passed_num[5];
} statistics;

void check(int i) {
  statistics.cnt++;
  int passed_num = 0;
  if (students[i].chinese < 60) statistics.chinese[1]++;
  else {
    statistics.chinese[0]++;
    passed_num++;
  }
  statistics.chinese[2] += students[i].chinese;
  if (students[i].math < 60) statistics.math[1]++;
  else {
    statistics.math[0]++;
    passed_num++;
  }
  statistics.math[2] += students[i].math;
  if (students[i].english < 60) statistics.english[1]++;
  else {
    statistics.english[0]++;
    passed_num++;
  }
  statistics.english[2] += students[i].english;
  if (students[i].programming < 60) statistics.programming[1]++;
  else {
    statistics.programming[0]++;
    passed_num++;
  }
  statistics.programming[2] += students[i].programming;

  statistics.passed_num[passed_num]++;
}

void stat()
{
  printf("Please enter class ID, 0 for the whole statistics.\n");
  int cid;
  memset(&statistics, 0, sizeof(statistics));
  scanf("%d", &cid);
  for (int i = 0; i < stu_num; i++)
  {
    
    if (!students[i].removed)
    {
      if (cid)
      {
        if (cid == students[i].CID) check(i);
      }
      else check(i);
    }
  }
  printf("Chinese\n");
  printf("Average Score: %2.2f\n", statistics.chinese[2] * 1.0 / statistics.cnt + 1e-5);
  printf("Number of passed students: %d\n", statistics.chinese[0]);
  printf("Number of failed students: %d\n\n", statistics.chinese[1]);
  
  printf("Mathematics\n");
  printf("Average Score: %2.2f\n", statistics.math[2] * 1.0 / statistics.cnt + 1e-5);
  printf("Number of passed students: %d\n", statistics.math[0]);
  printf("Number of failed students: %d\n\n", statistics.math[1]);

  printf("English\n");
  printf("Average Score: %2.2f\n", statistics.english[2] * 1.0 / statistics.cnt + 1e-5);
  printf("Number of passed students: %d\n", statistics.english[0]);
  printf("Number of failed students: %d\n\n", statistics.english[1]);

  printf("Programming\n");
  printf("Average Score: %2.2f\n", statistics.programming[2] * 1.0 / statistics.cnt + 1e-5);
  printf("Number of passed students: %d\n", statistics.programming[0]);
  printf("Number of failed students: %d\n\n", statistics.programming[1]);

  printf("Overall:\n");
  printf("Number of students who passed all subjects: %d\n", statistics.passed_num[4]);
  printf("Number of students who passed 3 or more subjects: %d\n", statistics.passed_num[4] + statistics.passed_num[3]);
  printf("Number of students who passed 2 or more subjects: %d\n", statistics.passed_num[4] + statistics.passed_num[3] + statistics.passed_num[2]);
  printf("Number of students who passed 1 or more subjects: %d\n", statistics.passed_num[4] + statistics.passed_num[3] + statistics.passed_num[2] + statistics.passed_num[1]);
  printf("Number of students who failed all subjects: %d\n\n", statistics.passed_num[0]);
}

int main()
{
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  while (1)
  {
    int choice;
    print_menu();
    scanf("%d", &choice);
    if (!choice) break;
    switch (choice)
    {
    case 1:
      add();
      break;
    case 2:
      DQ(0);
      break;
    case 3:
      DQ(1);
      break;
    case 4:
      printf("Showing the ranklist hurts students' self-esteem. Don't do that.\n");
      break;
    case 5:
      stat();
      break;
    }
  }
  return 0;
}
