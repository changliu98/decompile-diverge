int stbi__compute_transparency(struct stbi__png *png, struct stbi_uc *tr, int out_n)
{
  unsigned long i; unsigned long n = png->s->img_y * png->s->img_x;
  struct stbi_uc *out = png->out;
  ((void) sizeof ((out_n == 2 || out_n == 4) ? 1 : 0), __extension__ ({ if (out_n == 2 || out_n == 4) ; else __assert_fail ("out_n == 2 || out_n == 4", "func.c", 5026, __extension__ __PRETTY_FUNCTION__); }));
  if (out_n == 2)
    for (i = 0; i < n; ++i)
      out[1] = (out[0] == tr[0]) ? 0 : 0xff, out += 2;
  else
    for (i = 0; i < n; ++i)
      if (out[0] == tr[0] && out[1] == tr[1] && out[2] == tr[2])
        out[3] = 0, out += 4;
  return 1;
}