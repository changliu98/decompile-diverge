void __cdecl std::swap<float>(float *a, float *b)
{
  float t = *a;
  *a = *b;
  *b = t;
}