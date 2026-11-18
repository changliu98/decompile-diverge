void __cdecl std::swap<float>(float *valueA, float *valueB)
{
  float temp = *valueA;
  *valueA = *valueB;
  *valueB = temp;
}