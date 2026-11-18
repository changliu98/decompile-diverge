static char *
check_longlong_async_signal_safe(char *p, int *have_longlong)
{
 *have_longlong = 0;
 switch (*p) {
 case 'l':
  p++;
  if (*p != 'l') {
   *have_longlong = 1;
   break;
  }
  p++;
  *have_longlong = 1;
  break;
 default:
  return (p);
 }

 return (p);
}