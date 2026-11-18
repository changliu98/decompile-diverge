const char *__cdecl utf8_to_ucs4(const char *ptr, wchar_t *result)
{
  const char *v2; // rax
  int i; // [rsp+0h] [rbp-2Ch]
  char bits_count; // [rsp+4h] [rbp-28h]
  int octet_count; // [rsp+8h] [rbp-24h]
  int ch_0; // [rsp+Ch] [rbp-20h]
  int ch_0a; // [rsp+Ch] [rbp-20h]
  wchar_t ret; // [rsp+10h] [rbp-1Ch]
  const char *ptra; // [rsp+1Ch] [rbp-10h]

  ptra = ptr + 1;
  ch_0 = *(unsigned __int8 *)ptr;
  if ( (ch_0 & 0x80) == 0 )
  {
    if ( result )
      *result = ch_0;
    return ptra;
  }
  if ( (ch_0 & 0xE0) == 192 )
  {
    octet_count = 2;
    ch_0a = ch_0 & 0xFFFFFF1F;
    goto LABEL_16;
  }
  if ( (ch_0 & 0xF0) == 224 )
  {
    octet_count = 3;
    ch_0a = ch_0 & 0xFFFFFF0F;
    goto LABEL_16;
  }
  if ( (ch_0 & 0xF8) == 240 )
  {
    octet_count = 4;
    ch_0a = ch_0 & 0xFFFFFF07;
    goto LABEL_16;
  }
  if ( (ch_0 & 0xFC) == 248 )
  {
    octet_count = 5;
    ch_0a = ch_0 & 0xFFFFFF03;
    goto LABEL_16;
  }
  if ( (ch_0 & 0xFE) == 252 )
  {
    octet_count = 6;
    ch_0a = ch_0 & 0xFFFFFF01;
LABEL_16:
    bits_count = 6 * (octet_count - 1);
    ret = ch_0a << bits_count;
    for ( i = 1; i < octet_count; ++i )
    {
      bits_count -= 6;
      v2 = ptra++;
      if ( (*v2 & 0xC0) != 128 )
        return 0LL;
      ret |= (*v2 & 0x3F) << bits_count;
    }
    if ( result )
      *result = ret;
    return ptra;
  }
  return 0LL;
}