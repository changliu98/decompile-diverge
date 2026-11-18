void __cdecl process_bitmap_updates(STREAM s)
{
  uint8 *v1; // [rsp+0h] [rbp-80h]
  __int64 v2; // [rsp+8h] [rbp-78h]
  __int64 v3; // [rsp+10h] [rbp-70h]
  __int64 v4; // [rsp+18h] [rbp-68h]
  __int64 v5; // [rsp+20h] [rbp-60h]
  int y; // [rsp+30h] [rbp-50h]
  int i; // [rsp+34h] [rbp-4Ch]
  uint8 *bmpdata; // [rsp+38h] [rbp-48h]
  uint8 *bmpdataa; // [rsp+38h] [rbp-48h]
  unsigned __int8 *data; // [rsp+40h] [rbp-40h]
  uint16 size; // [rsp+4Ch] [rbp-34h]
  uint16 bufsize; // [rsp+4Eh] [rbp-32h]
  uint16 compress; // [rsp+50h] [rbp-30h]
  uint16 Bpp; // [rsp+52h] [rbp-2Eh]
  uint16 bpp; // [rsp+54h] [rbp-2Ch]
  uint16 cy; // [rsp+56h] [rbp-2Ah]
  uint16 cx_0; // [rsp+58h] [rbp-28h]
  uint16 height; // [rsp+5Ah] [rbp-26h]
  uint16 width; // [rsp+5Ch] [rbp-24h]
  uint16 bottom; // [rsp+5Eh] [rbp-22h]
  uint16 right; // [rsp+60h] [rbp-20h]
  uint16 top; // [rsp+62h] [rbp-1Eh]
  uint16 left; // [rsp+64h] [rbp-1Ch]
  uint16 num_updates; // [rsp+66h] [rbp-1Ah]

  logger(log_subject_t::Protocol, log_level_t::Debug, "%s()", "process_bitmap_updates");
  num_updates = *(_WORD *)s->p;
  s->p += 2;
  for ( i = 0; i < num_updates; ++i )
  {
    left = *(_WORD *)s->p;
    s->p += 2;
    top = *(_WORD *)s->p;
    s->p += 2;
    right = *(_WORD *)s->p;
    s->p += 2;
    bottom = *(_WORD *)s->p;
    s->p += 2;
    width = *(_WORD *)s->p;
    s->p += 2;
    height = *(_WORD *)s->p;
    s->p += 2;
    bpp = *(_WORD *)s->p;
    s->p += 2;
    Bpp = (bpp + 7) / 8;
    compress = *(_WORD *)s->p;
    s->p += 2;
    bufsize = *(_WORD *)s->p;
    s->p += 2;
    cx_0 = right - left + 1;
    cy = bottom - top + 1;
    LODWORD(v1) = bottom;
    LODWORD(v2) = width;
    LODWORD(v3) = height;
    LODWORD(v4) = Bpp;
    LODWORD(v5) = compress;
    logger(
      log_subject_t::Graphics,
      log_level_t::Debug,
      "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compression=%d",
      left,
      top,
      right,
      v1,
      v2,
      v3,
      v4,
      v5);
    if ( compress )
    {
      if ( (compress & 0x400) != 0 )
      {
        size = bufsize;
      }
      else
      {
        s->p += 2;
        size = *(_WORD *)s->p;
        s->p += 2;
        s->p += 4;
      }
      data = s->p;
      s->p += size;
      bmpdataa = (uint8 *)xmalloc(Bpp * height * (unsigned int)width);
      if ( bitmap_decompress(bmpdataa, width, height, data, size, Bpp) )
        ui_paint_bitmap(left, top, cx_0, cy, width, height, bmpdataa);
      else
        logger(log_subject_t::Graphics, log_level_t::Warning, "process_bitmap_updates(), failed to decompress bitmap");
      xfree(bmpdataa);
    }
    else
    {
      bmpdata = (uint8 *)xmalloc(Bpp * height * (unsigned int)width);
      for ( y = 0; y < height; ++y )
      {
        memcpy(&bmpdata[Bpp * width * (height - y - 1)], s->p, Bpp * width);
        s->p += Bpp * width;
      }
      ui_paint_bitmap(left, top, cx_0, cy, width, height, bmpdata);
      xfree(bmpdata);
    }
  }
}