size_t __cdecl spc_used(size_t head, size_t tail, size_t size)
{
  int diff; // [rsp+0h] [rbp-24h]

  diff = head - tail;
  if ( (int)head - (int)tail < 0 )
    return diff + size;
  else
    return diff;
}