void foo(int *line, int *pieces)
{
  int i;
  for (i = 0; i < 8 && pieces[i] == i + 2; i++)
    ;
  if (i == 8 && *line == 1) {
    *line = 8;
    for (i = 0; i < 8; i++)
      pieces[i] = i + 9;
  } else
    *line = 6;
}