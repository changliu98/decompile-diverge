unsigned int __cdecl scan_8long(const char *s, unsigned __int64 *u)
{
  unsigned __int64 c; // [rsp+0h] [rbp-28h]
  unsigned __int64 result; // [rsp+8h] [rbp-20h]
  unsigned int pos; // [rsp+14h] [rbp-14h]

  pos = 0;
  result = 0LL;
  while ( 1 )
  {
    c = (unsigned __int8)(s[pos] - 48);
    if ( c >= 8 )
      break;
    result = c + 8 * result;
    ++pos;
  }
  *u = result;
  return pos;
}