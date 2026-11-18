void __cdecl cpuid_detect(int *sse2, int *sse3)
{
  _RAX = 1LL;
  __asm { cpuid }
  if ( sse2 )
    *sse2 = ((int)_RDX >> 26) & 1;
  if ( sse3 )
    *sse3 = _RCX & 1;
}