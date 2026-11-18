void cpuid_detect(int *has_sse2, int *has_sse3)
{
  // Initialize sse2 pointer to 0 if it is not NULL
  if (has_sse2) *has_sse2 = 0;
  // Initialize sse3 pointer to 0 if it is not NULL
  if (has_sse3) *has_sse3 = 0;
}