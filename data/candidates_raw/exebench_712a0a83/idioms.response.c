void m1pos_inc(int *m1pos)
{
  (*m1pos)++;
  *m1pos = *m1pos % 61;
}