void
removespaces(char *to, char *from, int len)
{
 char *f = from;
 char *l = from + len - 1;

 if (*l && !*(l - 1))
  l--;

 while (f <= l) {
  if (*f == ' ')
   f++;
  else if (!*l || *l == ' ')
   l--;
  else
   break;
 }

 while ((*to++ = *f++) && f <= l);
 *to = '\0';
}