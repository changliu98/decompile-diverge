char *__cdecl PL__utf8_get_char(const char *in, int *chr)
{
  if ( (*in & 0xE0) == 192 && (in[1] & 0xC0) == 128 )
  {
    *chr = in[1] & 0x3F | ((*in & 0x1F) << 6);
    return (char *)(in + 2);
  }
  else if ( (*in & 0xF0) == 224 && (in[1] & 0xC0) == 128 && (in[2] & 0xC0) == 128 )
  {
    *chr = in[2] & 0x3F | ((in[1] & 0x3F) << 6) | ((*in & 0xF) << 12);
    return (char *)(in + 3);
  }
  else if ( (*in & 0xF8) == 240 && (in[1] & 0xC0) == 128 && (in[2] & 0xC0) == 128 && (in[3] & 0xC0) == 128 )
  {
    *chr = in[3] & 0x3F | ((in[2] & 0x3F) << 6) | ((in[1] & 0x3F) << 12) | ((*in & 7) << 18);
    return (char *)(in + 4);
  }
  else if ( (*in & 0xFC) == 248
         && (in[1] & 0xC0) == 128
         && (in[2] & 0xC0) == 128
         && (in[3] & 0xC0) == 128
         && (in[4] & 0xC0) == 128 )
  {
    *chr = in[4] & 0x3F | ((in[3] & 0x3F) << 6) | ((in[2] & 0x3F) << 12) | ((in[1] & 0x3F) << 18) | ((*in & 3) << 24);
    return (char *)(in + 5);
  }
  else if ( (*in & 0xFE) == 252
         && (in[1] & 0xC0) == 128
         && (in[2] & 0xC0) == 128
         && (in[3] & 0xC0) == 128
         && (in[4] & 0xC0) == 128
         && (in[5] & 0xC0) == 128 )
  {
    *chr = in[5] & 0x3F | ((in[4] & 0x3F) << 6) | ((in[3] & 0x3F) << 12) | ((in[2] & 0x3F) << 18) | ((in[1] & 0x3F) << 24) | ((*in & 1) << 30);
    return (char *)(in + 6);
  }
  else
  {
    *chr = *(unsigned __int8 *)in;
    return (char *)(in + 1);
  }
}