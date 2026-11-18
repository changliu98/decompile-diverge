int __cdecl ilog2(unsigned __int64 v)
{
  int l = 0;
  
  while ((1ULL << l) < v) {
    l++;
  }
  
  return l;
}