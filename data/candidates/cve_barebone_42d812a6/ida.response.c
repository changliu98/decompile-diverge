int __cdecl MPEG12_ParseSeqHdr(
        unsigned __int8 *pbuffer,
        u32 buflen,
        s32 *have_mpeg2,
        u32 *height,
        u32 *width,
        Double *frame_rate,
        Double *bitrate,
        u32 *aspect_ratio)
{
  u32 par; // [rsp+4h] [rbp-58h]
  int found; // [rsp+8h] [rbp-54h]
  u32 ix; // [rsp+Ch] [rbp-50h]
  u32 ixa; // [rsp+Ch] [rbp-50h]
  u32 scode; // [rsp+10h] [rbp-4Ch]
  int bitrate_int; // [rsp+18h] [rbp-44h]
  int aspect_code; // [rsp+20h] [rbp-3Ch]
  unsigned __int8 *pbufferb; // [rsp+4Ch] [rbp-10h]
  unsigned __int8 *pbufferc; // [rsp+4Ch] [rbp-10h]

  found = -1;
  *have_mpeg2 = 0;
  bitrate_int = 0;
  for ( ix = 0; ix < buflen - 6; ++ix )
  {
    scode = _byteswap_ulong(*(_DWORD *)pbuffer);
    if ( scode == 435 )
    {
      pbufferb = pbuffer + 4;
      *width = *pbufferb;
      *width *= 16;
      *width |= ((int)pbufferb[1] >> 4) & 0xF;
      *height = pbufferb[1] & 0xF;
      *height <<= 8;
      *height |= pbufferb[2];
      aspect_code = ((int)pbufferb[3] >> 4) & 0xF;
      if ( aspect_ratio )
      {
        par = 0;
        switch ( aspect_code )
        {
          case 2:
            par = 262147;
            break;
          case 3:
            par = 1048585;
            break;
          case 4:
            par = 131093;
            break;
          default:
            *aspect_ratio = 0;
            break;
        }
        *aspect_ratio = par;
      }
      *frame_rate = mpeg12_frame_rate_table[pbufferb[3] & 0xF];
      bitrate_int = (pbufferb[6] >> 6) | ((pbufferb[4] << 10) + 4 * pbufferb[5]);
      *bitrate = (double)bitrate_int;
      *bitrate = 400.0 * *bitrate;
      ix += 11;
      pbuffer = pbufferb + 7;
      found = 0;
    }
    else if ( !found )
    {
      if ( scode == 437 )
      {
        pbufferc = pbuffer + 4;
        ixa = ix + 4;
        if ( *pbufferc >> 4 == 1 )
        {
          *have_mpeg2 = 1;
          *height = *height & 0xFFF | (32 * (pbufferc[2] & 0x80)) | ((pbufferc[1] & 1) << 13);
          *width = *width & 0xFFF | ((pbufferc[2] & 0x60) << 7);
          bitrate_int |= ((pbufferc[3] >> 1) | ((pbufferc[2] & 0x1F) << 7)) << 18;
          *bitrate = (double)bitrate_int;
          *bitrate = 400.0 * *bitrate;
        }
        pbuffer = pbufferc + 1;
        ix = ixa + 1;
      }
      else if ( scode == 256 )
      {
        return 0;
      }
    }
    ++pbuffer;
  }
  return found;
}