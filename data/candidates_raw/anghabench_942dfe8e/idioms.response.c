int get_color(int i)
{
  int color = 0;
  if (i & 1) color = 4;
  if (i & 2) color |= 2;
  if (i & 4) color |= 1;
  return color;
}