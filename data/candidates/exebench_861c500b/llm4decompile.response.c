char *fix(char *d, char *s)
{
 int di = 0;
 int si = 0;

 while (s[si] != '\0') {
  if (s[si] == '\b') {
   di--;
   if (di < 0) di = 0;
  } else {
   d[di] = s[si];
   di++;
  }
  si++;
 }
 d[di] = '\0';

 return d;
}