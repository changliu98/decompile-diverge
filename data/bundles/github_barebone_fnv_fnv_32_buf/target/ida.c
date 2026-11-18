Fnv32_t __cdecl fnv_32_buf(void *buf, size_t len, Fnv32_t hval)
{
  unsigned __int8 *v3; // rax
  unsigned __int8 *bp_0; // [rsp+8h] [rbp-20h]

  for ( bp_0 = (unsigned __int8 *)buf; bp_0 < (unsigned __int8 *)((char *)buf + len); ++bp_0 )
  {
    v3 = bp_0;
    hval = (16777619 * hval) ^ *v3;
  }
  return hval;
}