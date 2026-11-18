int __cdecl sdscmp(const sds s1, const sds s2)
{
  int v2; // eax
  size_t v5; // [rsp+10h] [rbp-40h]
  int cmp; // [rsp+1Ch] [rbp-34h]
  size_t l2; // [rsp+28h] [rbp-28h]
  size_t l1; // [rsp+30h] [rbp-20h]

  l1 = sdslen(s1);
  l2 = sdslen(s2);
  if ( l1 >= l2 )
    v5 = l2;
  else
    v5 = l1;
  cmp = memcmp(s1, s2, v5);
  if ( cmp )
    return cmp;
  if ( l1 > l2 )
    return 1;
  v2 = 0;
  if ( l1 < l2 )
    return -1;
  return v2;
}