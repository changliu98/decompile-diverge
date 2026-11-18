void numconv(char *numstr)
{
 while (*numstr)
 {
  *numstr = *numstr - '0';
  numstr++;
 }
}