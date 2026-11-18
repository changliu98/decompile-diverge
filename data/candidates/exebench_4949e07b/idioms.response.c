void cftx020(struct complex *c)
{
  double x0 = c->re - c->im;
  double y0 = c->im + c->re;
  c->re = x0 + c->re;
  c->im = y0 + c->im;
  c->re = c->re - c->im;
  c->im = c->re + c->im;
}