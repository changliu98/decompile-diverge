int clip_wh(int *width, int *min_width, int min_val, int max_val)
{
  int xoff;
  if (*width < min_val) {
    xoff = min_val - *width;
    *width += xoff;
    *width = min_val;
    return xoff;
  }
  if (*width + *min_width >= max_val)
    *min_width = max_val - *width;
  return 0;
}