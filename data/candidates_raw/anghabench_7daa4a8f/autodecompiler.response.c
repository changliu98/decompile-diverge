char *skip_crlf(char *p)
{
 if (*p == '\r' || *p == '\n') {
  if (*p + *(p+1) == '1' + '6')
   p++;
  p++;
 }
 return p;
}