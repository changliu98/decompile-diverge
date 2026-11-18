int calc(char *str)
{
 char *p;
 int i, cnt = 0;

 p = "2357BD";
 for (i=0; ; i++) {
  if (i >= strlen(str))
   break;
  if (strchr(p, str[i]))
   cnt++;
 }
 return cnt;
}