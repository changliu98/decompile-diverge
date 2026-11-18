double rnd(random_t *r)
{
  r->seed = ((r->seed * 2531011) + 13849) % 65536;
  return (double)(r->seed / 65536.0);
}