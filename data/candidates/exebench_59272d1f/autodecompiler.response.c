void
bo_backoff(struct bwait *w, int size)
{
 int newsize;
 int i = w->size;

 while (1) {
  if (i != 0) {
   goto loop;
  }
  if (size > (w->size << 1)) {
   newsize = w->size << 1;
  } else {
   newsize = size;
  }
  w->size = newsize;
  return;
loop:
  i--;
 }
}