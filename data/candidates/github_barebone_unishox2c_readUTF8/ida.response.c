int32_t __cdecl readUTF8(const char *in, int len, int l, int *utf8len)
{
  int ret; // [rsp+0h] [rbp-1Ch]

  ret = 0;
  if ( l < len - 1 && (in[l] & 0xE0) == 192 && (in[l + 1] & 0xC0) == 128 )
  {
    *utf8len = 2;
    ret = ((in[l] & 0x1F) << 6) + (in[l + 1] & 0x3F);
    if ( ret < 128 )
      return 0;
  }
  else if ( l < len - 2 && (in[l] & 0xF0) == 224 && (in[l + 1] & 0xC0) == 128 && (in[l + 2] & 0xC0) == 128 )
  {
    *utf8len = 3;
    ret = ((((in[l] & 0xF) << 6) + (in[l + 1] & 0x3F)) << 6) + (in[l + 2] & 0x3F);
    if ( ret < 2048 )
      return 0;
  }
  else if ( l < len - 3
         && (in[l] & 0xF8) == 240
         && (in[l + 1] & 0xC0) == 128
         && (in[l + 2] & 0xC0) == 128
         && (in[l + 3] & 0xC0) == 128 )
  {
    *utf8len = 4;
    ret = ((((((in[l] & 7) << 6) + (in[l + 1] & 0x3F)) << 6) + (in[l + 2] & 0x3F)) << 6) + (in[l + 3] & 0x3F);
    if ( ret < 0x10000 )
      return 0;
  }
  return ret;
}