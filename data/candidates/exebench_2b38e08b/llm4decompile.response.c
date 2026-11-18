void copy_string(char *dst, char *src, int max)
{
  int i;
  int ok = 1;

  i = 0;
  while (ok)
    {
      if (i < max)
        {
          dst[i] = src[i];
          if (src[i] == 0)
            {
              ok = 0;
            }
        }
      else
        {
          ok = 0;
        }
      i++;
    }
}