int MPEG12_ParseSeqHdr(uchar *pbuffer,u32 buflen,s32 *have_mpeg2,u32 *height,u32 *width,
                      Double *frame_rate,Double *bitrate,u32 *aspect_ratio)

{
  uint uVar1;
  int iVar2;
  u32 par;
  s32 found;
  u32 ix;
  u32 scode;
  u32 bitrate_ext;
  u32 bitrate_int;
  u32 framerate_code;
  u32 aspect_code;
  Double *frame_rate_local;
  u32 *width_local;
  u32 *height_local;
  s32 *have_mpeg2_local;
  u32 buflen_local;
  uchar *pbuffer_local;
  
  found = -1;
  *have_mpeg2 = 0;
  bitrate_int = 0;
  ix = 0;
  pbuffer_local = pbuffer;
  do {
    if (buflen - 6 <= ix) {
      return found;
    }
    uVar1 = (uint)*pbuffer_local << 0x18 | (uint)pbuffer_local[1] << 0x10 |
            (uint)pbuffer_local[2] << 8 | (uint)pbuffer_local[3];
    if (uVar1 == 0x1b3) {
      *width = (uint)pbuffer_local[4];
      *width = *width << 4;
      *width = (int)(uint)pbuffer_local[5] >> 4 | *width;
      *height = pbuffer_local[5] & 0xf;
      *height = *height << 8;
      *height = (uint)pbuffer_local[6] | *height;
      iVar2 = (int)(uint)pbuffer_local[7] >> 4;
      if (aspect_ratio != (u32 *)0x0) {
        par = 0;
        if (iVar2 == 2) {
          par = 0x40003;
        }
        else if (iVar2 == 3) {
          par = 0x100009;
        }
        else if (iVar2 == 4) {
          par = 0x20015;
        }
        else {
          *aspect_ratio = 0;
        }
        *aspect_ratio = par;
      }
      *frame_rate = mpeg12_frame_rate_table[pbuffer_local[7] & 0xf];
      bitrate_int = (uint)pbuffer_local[8] * 0x400 + (uint)pbuffer_local[9] * 4 |
                    (uint)(pbuffer_local[10] >> 6);
      *bitrate = (double)bitrate_int;
      *bitrate = DAT_00102008 * *bitrate;
      ix = ix + 0xb;
      pbuffer_local = pbuffer_local + 0xb;
      found = 0;
    }
    else if (found == 0) {
      if (uVar1 == 0x1b5) {
        if (pbuffer_local[4] >> 4 == 1) {
          *have_mpeg2 = 1;
          *height = (pbuffer_local[5] & 1) << 0xd | (pbuffer_local[6] & 0xffffff80) << 5 |
                    *height & 0xfff;
          *width = (pbuffer_local[6] & 0x60) << 7 | *width & 0xfff;
          bitrate_int = bitrate_int |
                        ((pbuffer_local[6] & 0x1f) << 7 | (uint)(pbuffer_local[7] >> 1)) << 0x12;
          *bitrate = (double)bitrate_int;
          *bitrate = DAT_00102008 * *bitrate;
        }
        pbuffer_local = pbuffer_local + 5;
        ix = ix + 5;
      }
      else if (uVar1 == 0x100) {
        return 0;
      }
    }
    ix = ix + 1;
    pbuffer_local = pbuffer_local + 1;
  } while( true );
}