void __cdecl tableset(float SR, float dur, int size, float *tab)
{
  *tab = (float)(int)((float)(dur * SR) - 0.9999);
  tab[1] = (float)(size - 1);
}