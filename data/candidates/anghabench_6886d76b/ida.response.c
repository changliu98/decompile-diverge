int __cdecl ilog2(unsigned __int64 v)
{
  int l; // [rsp+0h] [rbp-Ch]

  for ( l = 0; 1LL << l < v; ++l )
    ;
  return l;
}