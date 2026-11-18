int __cdecl summe(int *n, int *s)
{
  if (*n) {
    *s += (*n)--;
    return summe(n, s) != 0;
  }
  return 1;
}