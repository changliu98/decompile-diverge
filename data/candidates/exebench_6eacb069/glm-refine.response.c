int __cdecl q_GetSizeOfMaxRegion(int *max_region)
{
  // The maximum region size is a constant 2 MB (0x200000 bytes)
  *max_region = 0x200000; 
  return 0; // Always returns 0 (success)
}