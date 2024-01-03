#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STR_MAX 10000001
#define PAT_MAX 3001

char str[STR_MAX] = {'\0'}, pat[PAT_MAX] = {'\0'};
int find_naive(char *);
int len_str, len_pat;
int idx[STR_MAX];
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
   rst = fopen("result_naive.txt", "w");
   fgets(str, STR_MAX, st);
   fgets(pat, PAT_MAX, pt);
   len_str = strlen(str);
   len_pat = strlen(pat);
   while (1)
   {
      int tmp;
      if (cnt == 0)
      {
         tmp = find_naive(str);
         if (tmp == -1)
            break;
         idx[0] = tmp;
         len_str -= tmp + 1;
         cnt++;
      }
      else
      {
         tmp = find_naive(str + idx[cnt - 1] + 1);
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
   printf("Program complete. Reulst saved to result_naive.txt\n");
   fclose(st);
   fclose(pt);
   fclose(rst);
   return 0;
}

int find_naive(char *string)
{
   int i, j = 0, start = 0, end;
   len_str = strlen(string);
   int last_s = len_str - 1;
   int last_p = len_pat - 1;
   end = last_p;
   for (i = 0; end <= last_s; end++, start++)
   {
      if (string[end] == pat[last_p])
         for (j = 0, i = start; j < last_p && string[i] == pat[j]; i++, j++)
            ;
      if (j == last_p)
         return start;
   }
   return -1;
}
