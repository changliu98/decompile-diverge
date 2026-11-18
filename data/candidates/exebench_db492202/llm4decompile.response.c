void tableset(float *tab, float SR, int size, float dur)
{
  tab[0] = (float) (dur * SR - 1.0);
  tab[1] = (float) (size - 1);
}