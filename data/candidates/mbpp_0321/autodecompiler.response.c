char *func0(char *str)
{
 int len = strlen(str);
 int i, j;
 int k = 0;

 for (i = 1; ; i++) {
  if (i > len) break;
  k += sprintf(func0_res+k,"%d",i);
 }

 for (j = len-1; ; j--) {
  if (j <= 0) break;
  k += sprintf(func0_res+k,"%d",j);
 }

 func0_res[k] = '\0';
 return func0_res;
}