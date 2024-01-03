#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STR_MAX 10000001
#define PAT_MAX 3001

char str[STR_MAX] = {'\0'}, pat[PAT_MAX] = {'\0'};
void makeT(void);
int find_kmp(char *);
int len_str, len_pat;
int idx[STR_MAX], T[PAT_MAX];
int main()
{
   FILE *st, *pt, *rst;
   int cnt = 0;
   st = fopen("string.txt", "r");
   if (st == NULL)
   {
      printf("string file not found.\n");
      return 0;
   }
   pt = fopen("pattern.txt", "r");
   if (pt == NULL)
   {
      printf("pattern file not found.\n");
      return 0;
   }
   rst = fopen("result_kmp.txt", "w");
   fgets(str, STR_MAX, st);
   fgets(pat, PAT_MAX, pt);
   len_str = strlen(str);
   len_pat = strlen(pat);
   makeT();
   while (1)
   {
      int tmp;
      if (cnt == 0)
      {
         tmp = find_kmp(str);
         if (tmp == -1)
            break;
         idx[0] = tmp;
         len_str -= tmp + 1;
         cnt++;
      }
      else
      {
         tmp = find_kmp(str + idx[cnt - 1] + 1);
         if (tmp == -1)
            break;
         idx[cnt] = tmp + idx[cnt - 1] + 1;
         cnt++;
      }
   }
   fprintf(rst, "%d\n", cnt);
   for (int i = 0; i < cnt; i++)
      fprintf(rst, "%d ", idx[i]);
   fprintf(rst, "\n");
   printf("Program complete. Reulst saved to result_kmp.txt\n");
   fclose(st);
   fclose(pt);
   fclose(rst);
   return 0;
}

int find_kmp(char *string)
{
   int i = 0, j = 0;
   int lens = strlen(string);
   int lenp = len_pat;
   while (i < lens && j < lenp)
   {
      if (string[i] == pat[j])
      {
         i++;
         j++;
      }
      else if (j == 0)
         i++;
      else
         j = T[j - 1] + 1;
   }
   if (j == lenp)
      return i - lenp;
   return -1;
}

void makeT(void)
{
   int i, j;
   T[0] = -1;
   for (j = 1; j < len_pat; j++)
   {
      i = T[j - 1];
      while ((pat[j] != pat[i + 1]) && (i >= 0))
         i = T[i];
      if (pat[j] == pat[i + 1])
         T[j] = i + 1;
      else
         T[j] = -1;
   }
}