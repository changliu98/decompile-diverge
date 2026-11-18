void __cdecl grad1(int hash, float *gx)
{
  *gx = (float)(hash & 7) + 1.0f;
  if ( hash & 8 )
    *(int *)gx ^= 0x80000000;
}