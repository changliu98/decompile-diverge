void __cdecl clamp(int *a, int *b, const int max)
{
  // Calculate how many times 'max' fits into '*a' and add it to '*b'
  *b += *a / max;
  
  // Store the remainder of '*a / max' back into '*a'
  *a %= max;
}