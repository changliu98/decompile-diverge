int *__cdecl func0(const char *values, int *size)
{
  int v2; // eax
  bool v4; // [rsp+2h] [rbp-2Eh]
  bool v5; // [rsp+3h] [rbp-2Dh]
  int val; // [rsp+4h] [rbp-2Ch]
  char *end; // [rsp+8h] [rbp-28h] BYREF
  const char *start; // [rsp+10h] [rbp-20h]
  int count; // [rsp+1Ch] [rbp-14h]
  int *sizea; // [rsp+20h] [rbp-10h]
  const char *valuesa; // [rsp+28h] [rbp-8h]

  valuesa = values;
  sizea = size;
  count = 0;
  for ( start = values; *start; start = end )
  {
    while ( 1 )
    {
      v5 = 0;
      if ( *start )
      {
        v5 = 0;
        if ( ((*__ctype_b_loc())[*start] & 0x800) == 0 )
          v5 = *start != 45;
      }
      if ( !v5 )
        break;
      ++start;
    }
    if ( !*start )
      break;
    val = strtol(start, &end, 10);
    if ( start == end || *end != 44 && *end )
    {
      while ( 1 )
      {
        v4 = 0;
        if ( *end )
          v4 = *end != 44;
        if ( !v4 )
          break;
        ++end;
      }
    }
    else
    {
      v2 = count++;
      func0_out[v2] = val;
    }
  }
  *sizea = count;
  return func0_out;
}