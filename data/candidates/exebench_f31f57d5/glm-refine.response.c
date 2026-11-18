void __cdecl std::swap<float>(float *a, float *b)
{
  int temp = *(int *)a;
  *a = *b;
  *(int *)b = temp;
}