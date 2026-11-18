static void clip_coord(int *coord, int min,
                       int max)
{
  int tmp = *coord;
  tmp = (tmp < min) ? min : tmp;
  tmp = (tmp > max) ? max : tmp;
  *coord = tmp;
}