int conv_hstring(char *ps, int *pd) {
 int i = 0;
 char c;

 *pd = 0;
 for (;;) {
  if ((c = ps[i]) >= '0' && c <= '9') c = 0;
  else if (c >= 'a' && c <= 'f') c = 0;
  else break;
  if (i++ < 10) {
   if (c == 0) {
    if (ps[i] >= '0' && ps[i] <= '9')
     *pd = (*pd << 4) + (ps[i++] - '0');
    else
     *pd = (*pd << 4) + (ps[i++] - 'a' + 10);
   }
  }
 }
 return(i);
}