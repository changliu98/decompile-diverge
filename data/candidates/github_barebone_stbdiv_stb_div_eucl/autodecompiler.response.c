int stb_div_eucl(int x, int y) {
  int q;
  int r;
  if (x >= 0) {
    if (y >= 0)
      q = x / y, r = x - q * y;
    else
      if (y != (-2147483647-1))
        q = -(x / -y), r = x - q * y;
      else
        q = 0, r = x;
  } else {
    if (x != (-2147483647-1))
      if (y >= 0)
        q = -((0-x) / y), r = -(0-x - q * y);
      else
        if (y != (-2147483647-1))
          q = (0-x) / -y, r = -(0-x - q * y);
        else
          q = 1, r = x - q * y;
    else
      if (y >= 0)
        q = -((0-(0-y)) / y) - 1, r = -(0-(0-y) - q * y);
      else
        if (y != (-2147483647-1))
          q = ((0-(0-y)) / -y) + 1, r = -((0-(0-y)) - q * y);
        else
          q = 1, r = 0;
  }
  if (r >= 0)
    return q;
  else
    return q + (y > 0 ? -1 : 1);
}