void __fastcall std::swap<float>(float *a, float *b)
{
  float temp = *a;
  *a = *b;
  *b = temp;
}