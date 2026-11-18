void stack4_push(unsigned long *d, unsigned long s)
{
  unsigned long t = *d;
  t = t << 4;
  t = t | s;
  *d = t;
}