void advance_m1pos(int *m1pos)
{
  (*m1pos)++;
  *m1pos = *m1pos % 61;
}