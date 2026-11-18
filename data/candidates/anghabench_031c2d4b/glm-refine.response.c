bool __cdecl tomoyo_invalid(const unsigned __int8 c)
{
  if (c == 0)
    return false;
    
  if (c <= 0x20)
    return true;
    
  return c >= 0x7F;
}