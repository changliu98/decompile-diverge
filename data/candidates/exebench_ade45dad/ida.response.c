void __cdecl zywrle_calc_size(int *w, int *h, int level)
{
  *w &= ~((1 << level) - 1);
  *h &= ~((1 << level) - 1);
}