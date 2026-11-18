int
dupfd(int from, int *to)
{
 int ret;

 if (from == -1) {
  *to = -1;
  ret = 1;
 } else {
  *to = dup(from);
  if (*to == -1)
   ret = 0;
  else
   ret = 1;
 }
 return ret;
}