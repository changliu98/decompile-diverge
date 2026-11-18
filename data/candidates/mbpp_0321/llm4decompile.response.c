char *func0(char *arg)
{
 int i, pos, len;

 len = strlen(arg);
 pos = 0;
 for (i = 1; i <= len; i++)
  pos += sprintf(func0::res + pos, "%d", i);
 for (i = len - 1; i >= 1; i--)
  pos += sprintf(func0::res + pos, "%d", i);
 func0::res[pos] = '\0';

 return func0::res;
}