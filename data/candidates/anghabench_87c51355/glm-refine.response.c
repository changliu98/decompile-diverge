size_t __cdecl spc_used(size_t head, size_t tail, size_t size)
{
  int diff = (int)head - (int)tail;
  
  if (diff < 0)
    return diff + size;
  else
    return diff;
}