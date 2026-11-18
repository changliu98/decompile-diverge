int __cdecl ff_amf_get_field_value(
        const uint8_t *data,
        const uint8_t *data_end,
        const uint8_t *name,
        uint8_t *dst,
        int dst_size)
{
  const uint8_t *v5; // rax
  const char *v6; // rcx
  int v8; // [rsp+Ch] [rbp-74h]
  int v9; // [rsp+20h] [rbp-60h]
  bool v10; // [rsp+27h] [rbp-59h]
  int size; // [rsp+28h] [rbp-58h]
  int len; // [rsp+2Ch] [rbp-54h]
  int lena; // [rsp+2Ch] [rbp-54h]
  int lenb; // [rsp+2Ch] [rbp-54h]
  int namelen; // [rsp+30h] [rbp-50h]
  const uint8_t *dataa; // [rsp+50h] [rbp-30h] BYREF
  const uint8_t **v21; // [rsp+60h] [rbp-20h]
  const uint8_t **p_dataa; // [rsp+68h] [rbp-18h]
  unsigned __int64 v23; // [rsp+70h] [rbp-10h]
  unsigned __int64 v24; // [rsp+78h] [rbp-8h]

  dataa = data;
  namelen = strlen((const char *)name);
  while ( 1 )
  {
    v10 = 0;
    if ( *dataa != 3 )
      v10 = dataa < data_end;
    if ( !v10 )
      break;
    len = ff_amf_tag_size(dataa, data_end);
    if ( len < 0 )
      len = (_DWORD)data_end - (_DWORD)dataa;
    dataa += len;
  }
  if ( data_end - dataa < 3 )
    return -1;
  ++dataa;
  while ( 1 )
  {
    p_dataa = &dataa;
    dataa += 2;
    size = *(dataa - 1) | (*(dataa - 2) << 8);
    if ( !size )
      return -1;
    if ( size < 0 || size >= data_end - dataa )
      return -1;
    dataa += size;
    if ( size == namelen && !memcmp(&dataa[-size], name, namelen) )
      break;
    lenb = ff_amf_tag_size(dataa, data_end);
    if ( lenb < 0 || lenb >= data_end - dataa )
      return -1;
    dataa += lenb;
  }
  v5 = dataa++;
  v9 = *v5;
  if ( *v5 )
  {
    if ( v9 == 1 )
    {
      v6 = "false";
      if ( *dataa )
        v6 = "true";
      snprintf((char *)dst, dst_size, "%s", v6);
    }
    else
    {
      if ( v9 != 2 )
        return -1;
      v21 = &dataa;
      dataa += 2;
      lena = *(dataa - 1) | (*(dataa - 2) << 8);
      if ( lena + 1 <= dst_size )
        v8 = lena + 1;
      else
        v8 = dst_size;
      av_strlcpy((char *)dst, (const char *)dataa, v8);
    }
  }
  else
  {
    v24 = _byteswap_uint64(*(_QWORD *)dataa);
    v23 = v24;
    snprintf((char *)dst, dst_size, "%g", *(double *)&v24);
  }
  return 0;
}