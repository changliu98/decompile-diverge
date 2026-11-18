char *__cdecl func0(int n)
{
  int i_0; // [rsp+4h] [rbp-2Ch]
  char *ptr; // [rsp+8h] [rbp-28h]
  char *out; // [rsp+10h] [rbp-20h]
  int i; // [rsp+1Ch] [rbp-14h]
  int len; // [rsp+20h] [rbp-10h]

  len = 2;
  for ( i = 1; i <= n; ++i )
    len += snprintf(0LL, 0LL, " %d", (unsigned int)i);
  out = (char *)malloc(len);
  if ( !out )
    return 0LL;
  ptr = &out[sprintf(out, "0")];
  for ( i_0 = 1; i_0 <= n; ++i_0 )
    ptr += sprintf(ptr, " %d", (unsigned int)i_0);
  return out;
}