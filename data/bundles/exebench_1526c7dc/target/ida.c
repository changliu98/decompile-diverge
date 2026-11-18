void __cdecl atomic_and(volatile size_t *x, size_t val)
{
  signed __int64 v2; // rtt
  signed __int64 v3; // [rsp+10h] [rbp-18h]

  v3 = *x;
  do
  {
    v2 = v3;
    v3 = _InterlockedCompareExchange64((volatile signed __int64 *)x, val & v3, v3);
  }
  while ( v2 != v3 );
}