unsigned __int64 __cdecl it_advance(unsigned __int64 cpsr)
{
  if ( (cpsr & 0x6000400) != 0 )
    return cpsr & 0xFFFFFFFFF9FFE3FFLL | ((2 * (cpsr & 0x6001C00)) | (unsigned int)((2 * (cpsr & 0x6001C00)) >> 17)) & 0x6001C00;
  else
    return cpsr & ~PSR_IT_MASK;
}