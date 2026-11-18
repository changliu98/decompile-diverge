unsigned __int64 __cdecl do_csum(const unsigned __int8 *buff, int len, unsigned __int64 result)
{
  unsigned __int64 resulta; // [rsp+0h] [rbp-18h]

  resulta = result;
  if ( ((unsigned __int8)buff & 2) != 0 )
    return result + 1;
  return resulta;
}