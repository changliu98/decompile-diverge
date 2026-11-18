int ISORegexp__get_cclass(char *pattern, int ppos, int *len, int *from, int *to, int *reverse)
{
 int cclass;

 if (pattern[ppos] == '^') {
  *reverse = 1;
  ppos++;
 } else {
  *reverse = 0;
 }
 switch (pattern[ppos]) {
 case ' ':
  *len = 1;
  cclass = 3;
  break;
 case '%':
  ppos++;
  *len = 2;
  switch (pattern[ppos]) {
  case 'd':
   cclass = 2;
   break;
  case 'c':
   cclass = 1;
   break;
  case 'C':
   cclass = 4;
   break;
  case 'i':
   cclass = 5;
   break;
  case 'p':
   cclass = 6;
   break;
  case 'P':
   cclass = 7;
   break;
  case 't':
   cclass = 9;
   break;
  default:
   *from = ppos;
   *to = ppos;
   cclass = 8;
   break;
  }
  break;
 case '[':
  *from = ppos + 2;
  while (pattern[ppos] && pattern[ppos] != ']')
   ppos++;
  *to = ppos - 1;
  *len = *to - *from + 1;
  cclass = 8;
  break;
 default:
  *len = 1;
  *from = ppos;
  *to = ppos;
  cclass = 8;
  break;
 }
 return cclass;
}