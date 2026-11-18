unsigned __int64 __cdecl do_csum(const unsigned __int8 *buff, int len, unsigned __int64 result)
{
  // If the buffer pointer is not 4-byte aligned (specifically, if the 2-bit is set),
  // return the initial result incremented by 1.
  if ( (unsigned __int64)buff & 2 )
    return result + 1;

  // Otherwise, return the unmodified initial result.
  return result;
}