int MPEG12_ParseSeqHdr(unsigned char *pbuffer, unsigned int buflen, int *have_mpeg2, int *height, int *width, double *frame_rate, double *bitrate, unsigned int *aspect_ratio)
{
  unsigned int scode;
  unsigned int ix;
  int found = -1;
  int aspect_code;
  int bitrate_int = 0;
  unsigned char *pbufferb;
  unsigned char *pbufferc;
  unsigned int par = 0;
  *have_mpeg2 = 0;
  for (ix = 0; ix < (buflen - 6); ++ix, ++pbuffer)
  {
    scode = pbuffer[0] | (pbuffer[1]<<8) | (pbuffer[2]<<16) | (pbuffer[3]<<24);
    if (scode == 0x00000101)
    {
      pbufferb = pbuffer + 4;
      *width = pbufferb[0];
      *width = (*width << 4) & 0xf00;
      *width = (*width | (pbufferb[1] >> 4)) & 0xfff;
      *height = pbufferb[1] & 0xf;
      *height = (*height << 8) & 0xff00;
      *height = (*height | pbufferb[2]) & 0xfff;
      aspect_code = (pbufferb[3] >> 4) & 0xf;
      if (aspect_ratio != ((void *)0))
      {
        par = 0;
        switch (aspect_code)
        {
          case 2:
            par = 0x00040101;
            break;
          case 3:
            par = 0x00050101;
            break;
          case 4:
            par = 0x00010101;
            break;
          default:
            *aspect_ratio = 0;
            break;
        }
        *aspect_ratio = par;
      }
      *frame_rate = mpeg12_frame_rate_table[(pbufferb[3] & 0xf)];
      bitrate_int = (pbufferb[4] << 10) & 0x3fc00;
      bitrate_int = (bitrate_int + pbufferb[5]) & 0xfffc;
      bitrate_int = (bitrate_int + pbufferb[6]) & 0xfffc;
      bitrate_int = (bitrate_int >> 6) & 0x3ff;
      *bitrate = (double) bitrate_int;
      *bitrate = *bitrate * 400.0;
      ix = ix + 11;
      pbuffer = pbufferb + 7;
      found = 0;
    }
    else if (found == 0)
    {
      if (scode == 0x00000103)
      {
        pbufferc = pbuffer + 4;
        ix = ix + 4;
        if ((pbufferc[0] >> 4) == 1)
        {
          *have_mpeg2 = 1;
          *height = *height & 0xfff;
          *height = *height | ((pbufferc[2] & 0x80) << 5);
          *height = *height | ((pbufferc[1] & 0x1) << 13);
          *width = *width & 0xfff;
          *width = *width | ((pbufferc[2] & 0x60) << 7);
          bitrate_int = (pbufferc[3] >> 1) & 0x1ff;
          bitrate_int = (bitrate_int | (pbufferc[2] & 0x1f) << 7) & 0x1ff;
          bitrate_int = (bitrate_int << 18) & 0x1ff00000;
          *bitrate = (double) bitrate_int;
          *bitrate = *bitrate * 400.0;
        }
        pbuffer = pbufferc + 1;
        ix = ix + 1;
      }
      else if (scode == 0x00000100)
      {
        return 0;
      }
    }
  }
  return found;
}