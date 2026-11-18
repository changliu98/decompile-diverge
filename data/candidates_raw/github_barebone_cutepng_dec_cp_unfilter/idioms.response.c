int decompress(int width, int height, int bpp, char *in)
{
  int i; int j;
  int len;
  char *prev;
  char *inptr;
  inptr = in;
  len = bpp * width;
  if (height > 0)
  {
    inptr++;
    switch (*inptr)
    {
      case 0:
      case 2:
        break;
      case 1:
        for (i = bpp; i < len; i++)
        {
          inptr[i] += inptr[i - bpp];
        }
        break;
      case 3:
        for (i = bpp; i < len; i++)
        {
          inptr[i] += inptr[i - bpp] / 2;
        }
        break;
      case 4:
        for (i = bpp; i < len; i++)
        {
          inptr[i] += interpolate(inptr[i - bpp], 0, 0);
        }
        break;
      default:
        return 0;
    }
  }
  else
  {
    prev = inptr;
    inptr += len;
    for (j = 1; j < height; j++)
    {
      inptr++;
      switch (*inptr)
      {
        case 0:
          break;
        case 1:
          for (i = 0; i < bpp; i++)
          {
            inptr[i] = inptr[i];
          }
          for (i = bpp; i < len; i++)
          {
            inptr[i] += inptr[i - bpp];
          }
          break;
        case 2:
          for (i = 0; i < bpp; i++)
          {
            inptr[i] += prev[i];
          }
          for (i = bpp; i < len; i++)
          {
            inptr[i] += prev[i];
          }
          break;
        case 3:
          for (i = 0; i < bpp; i++)
          {
            inptr[i] += prev[i] / 2;
          }
          for (i = bpp; i < len; i++)
          {
            inptr[i] += (prev[i] + inptr[i - bpp]) / 2;
          }
          break;
        case 4:
          for (i = 0; i < bpp; i++)
          {
            inptr[i] += prev[i];
          }
          for (i = bpp; i < len; i++)
          {
            inptr[i] += interpolate(inptr[i - bpp], prev[i], prev[i - bpp]);
          }
          break;
        default:
          return 0;
      }
      prev = inptr;
      inptr += len;
    }
  }
  return 1;
}