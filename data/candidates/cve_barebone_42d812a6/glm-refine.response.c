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
  u32 par;
  int found = -1;
  u32 ix;
  u32 scode;
  int bitrate_int = 0;

  *have_mpeg2 = 0;

  // Prevent underflow if buflen is less than 7
  if (buflen < 7)
    return found;

  for (ix = 0; ix < buflen - 6; ++ix)
  {
    // Read 32-bit big-endian start code
    scode = _byteswap_ulong(*(_DWORD *)pbuffer);

    // 0x000001B3: Sequence Header (MPEG-1 / MPEG-2)
    if (scode == 0x000001B3)
    {
      unsigned __int8 *seq_hdr = pbuffer + 4;

      // Horizontal Size (12 bits)
      *width = (seq_hdr[0] << 4) | (seq_hdr[1] >> 4);

      // Vertical Size (12 bits)
      *height = ((seq_hdr[1] & 0x0F) << 8) | seq_hdr[2];

      // Aspect Ratio Information (4 bits)
      int aspect_code = seq_hdr[3] >> 4;
      if (aspect_ratio)
      {
        par = 0;
        switch (aspect_code)
        {
          case 2: par = 262147;   break; // 4:3
          case 3: par = 1048585;  break; // 16:9
          case 4: par = 131093;   break; // 2.21:1
          default: *aspect_ratio = 0; break;
        }
        *aspect_ratio = par;
      }

      // Frame Rate Code (4 bits)
      *frame_rate = mpeg12_frame_rate_table[seq_hdr[3] & 0x0F];

      // Bit Rate (18 bits)
      bitrate_int = (seq_hdr[4] << 10) | (seq_hdr[5] << 2) | (seq_hdr[6] >> 6);
      *bitrate = (double)bitrate_int * 400.0;

      // Advance pointers and indices
      ix += 11;
      pbuffer = seq_hdr + 7;
      found = 0;
    }
    else if (!found)
    {
      // 0x000001B5: Extension Start Code (MPEG-2)
      if (scode == 0x000001B5)
      {
        unsigned __int8 *ext_start = pbuffer + 4;
        u32 next_ix = ix + 4;

        // Sequence Extension ID == 1
        if (ext_start[0] >> 4 == 1)
        {
          *have_mpeg2 = 1;

          // Extended Vertical Size (13 bits total)
          *height = (*height & 0x0FFF) 
                  | ((ext_start[1] & 0x01) << 13) 
                  | ((ext_start[2] & 0x80) << 5);

          // Extended Horizontal Size (14 bits total)
          *width = (*width & 0x0FFF) 
                 | ((ext_start[2] & 0x60) << 7);

          // Extended Bit Rate (30 bits total)
          bitrate_int |= ((ext_start[2] & 0x1F) << 7) | (ext_start[3] >> 1) << 18;
          *bitrate = (double)bitrate_int * 400.0;
        }

        pbuffer = ext_start + 1;
        ix = next_ix + 1;
      }
      // 0x00000100: Picture Start Code
      else if (scode == 0x00000100)
      {
        return 0;
      }
    }
    ++pbuffer;
  }
  return found;
}