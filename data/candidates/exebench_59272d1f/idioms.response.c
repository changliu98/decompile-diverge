void bo_backoff(int *bwait, int cap)
{
  int i = *bwait;
  int newsize;
  while (i) {
    i--;
  }
  if (2 * *bwait < cap)
    newsize = 2 * *bwait;
  else
    newsize = cap;
  *bwait = newsize;
}