void __cdecl insert_dle(unsigned __int8 *dest, unsigned __int8 *src, int count)
{
  while (count--)
  {
    // Copy byte from src to dest, then advance both pointers
    *dest++ = *src++;

    // If the byte we just copied was a DLE, append an extra DLE for escaping
    if (src[-1] == DLE)
    {
      *dest++ = DLE;
    }
  }
}