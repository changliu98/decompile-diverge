void nextm2pos(int *m2pos)
{
  (*m2pos)++;
  *m2pos = *m2pos % 37;
}