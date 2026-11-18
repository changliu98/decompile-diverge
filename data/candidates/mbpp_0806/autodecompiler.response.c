int func0(char *s)
{
 int len;
 int i;
 int max = 0;
 int tmp = 0;

 len = strlen(s);
 i = 0;
 while (1) {
  if (i >= len)
   break;
  if (___ctype_b_loc()[(s[i])] & 256) {
   tmp++;
  } else {
   if (tmp > max)
    max = tmp;
   tmp = 0;
  }
  i++;
 }

 if (___ctype_b_loc()[(s[len-1])] & 256) {
  if (tmp > max)
   max = tmp;
 }

 return max;
}