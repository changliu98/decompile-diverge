void set_translation(struct _mat2 *t, float x, float y)
{
  t->c1 = 1.0f;
  t->c2 = 0.0f;
  t->c3 = 0.0f;
  t->c4 = 1.0f;
  t->c5 = x;
  t->c6 = y;
}