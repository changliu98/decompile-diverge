int parse_width(const char *fmt, int *len_p)
{
 int width = 0;
 int len = 0;

 while (fmt[len] && fmt[len] >= '0' && fmt[len] <= '9')
  width = width * 10 + fmt[len++] - '0';

 *len_p = len;
 return width;
}