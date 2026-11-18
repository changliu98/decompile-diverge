int32_t __cdecl readUTF8(const char *in, int len, int l, int *utf8len)
{
  int ret = 0;

  // 2-byte sequence: 110xxxxx 10xxxxxx
  // Original check: l < len - 1 (equivalent to l + 1 < len)
  if ( l + 1 < len && (in[l] & 0xE0) == 0xC0 && (in[l + 1] & 0xC0) == 0x80 )
  {
    *utf8len = 2;
    ret = ((in[l] & 0x1F) << 6) | (in[l + 1] & 0x3F);
    
    // Reject overlong encodings (code points that should be in 1 byte)
    if ( ret < 0x80 )
      return 0;
  }
  // 3-byte sequence: 1110xxxx 10xxxxxx 10xxxxxx
  // Original check: l < len - 2 (equivalent to l + 2 < len)
  else if ( l + 2 < len && (in[l] & 0xF0) == 0xE0 && (in[l + 1] & 0xC0) == 0x80 && (in[l + 2] & 0xC0) == 0x80 )
  {
    *utf8len = 3;
    ret = ((in[l] & 0x0F) << 12) | ((in[l + 1] & 0x3F) << 6) | (in[l + 2] & 0x3F);
    
    // Reject overlong encodings (code points that should be in 2 bytes)
    if ( ret < 0x800 )
      return 0;
  }
  // 4-byte sequence: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
  // Original check: l < len - 3 (equivalent to l + 3 < len)
  else if ( l + 3 < len && (in[l] & 0xF8) == 0xF0 && (in[l + 1] & 0xC0) == 0x80 && (in[l + 2] & 0xC0) == 0x80 && (in[l + 3] & 0xC0) == 0x80 )
  {
    *utf8len = 4;
    ret = ((in[l] & 0x07) << 18) | ((in[l + 1] & 0x3F) << 12) | ((in[l + 2] & 0x3F) << 6) | (in[l + 3] & 0x3F);
    
    // Reject overlong encodings (code points that should be in 3 bytes)
    if ( ret < 0x10000 )
      return 0;
  }

  return ret;
}