void swap(void *ap, void *bp)
{
  char *a = ap;
  char *b = bp;
  char t = *a;
  *a = *b;
  *b = t;
}