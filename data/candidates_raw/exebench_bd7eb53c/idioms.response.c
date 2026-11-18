void set_level(int *w, int *h, int level)
{
  *w = *w & ~((1 << level)-1);
  *h = *h & ~((1 << level)-1);
}