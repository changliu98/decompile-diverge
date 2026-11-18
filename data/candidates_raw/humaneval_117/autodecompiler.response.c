char** fun(char* line, int k, int* returnSize)
{
 char *vowels = "aeiouAEIOU";
 char **ret = NULL;
 int i, j, l, m, n, cnt, start, end;
 size_t len;
 char *tmp;

 cnt = 0;
 n = 0;
 m = 0;
 len = strlen(line);
 tmp = (char *)malloc(len + 1);

 for (i = 0; ; i++) {
  if (i > len) break;
  if ((iswspace(line[i]) || !line[i])) {
   if (cnt == k) {
    tmp[i - start] = '\0';
    ret = (char **)realloc(ret, (m + 1) * sizeof(char *));
    ret[m] = (char *)malloc(strlen(tmp) + 1);
    strcpy(ret[m], tmp);
    m++;
   }
   start = i + 1;
   cnt = 0;
  } else {
   tmp[i - start] = line[i];
   if (strchr(vowels, line[i]) == NULL && iswcntrl(line[i]) == 0) {
    cnt++;
   }
  }
 }

 free(tmp);
 *returnSize = m;
 return *ret;
}