char *
_getbase(char *p, int *basep)
{
 if (*p != '0')
  *basep = 10;
 else switch (*++p) {
 case 'x':
  *basep = 16;
  break;
 case 't':
 case 'n':
  *basep = 10;
  break;
 case 'o':
  *basep = 8;
  break;
 default:
  *basep = 10;
  return (--p);
 }
 return (++p);
}