void __cdecl nvgTransformTranslate(float *t, float tx, float ty)
{
  *t = 1.0;
  t[1] = 0.0;
  t[2] = 0.0;
  t[3] = 1.0;
  t[4] = tx;
  t[5] = ty;
}