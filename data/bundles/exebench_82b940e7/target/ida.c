void __cdecl clamp(int *a, int *b, const int max)
{
  *b += *a / max;
  *a %= max;
}