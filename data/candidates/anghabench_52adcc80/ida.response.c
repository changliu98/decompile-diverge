unsigned __int16 __cdecl BigUnsignedShort(unsigned __int16 l)
{
  return HIBYTE(l) + ((unsigned __int8)l << 8);
}