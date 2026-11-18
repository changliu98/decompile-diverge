void bo_backoff(int *bwait, int cap)
{
 int i;

 for (i = *bwait; i != 0; i--)
  ;

 if (2 * *bwait < cap)
  *bwait = 2 * *bwait;
 else
  *bwait = cap;
}