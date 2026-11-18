BOOL __cdecl resize_vbar_entry(CLEAR_CONTEXT *clear, CLEAR_VBAR_ENTRY *vBarEntry)
{
  BYTE *tmp; // [rsp+0h] [rbp-30h]
  UINT32 diffSize; // [rsp+Ch] [rbp-24h]
  UINT32 oldPos; // [rsp+10h] [rbp-20h]
  UINT32 bpp; // [rsp+14h] [rbp-1Ch]

  if ( vBarEntry->count > vBarEntry->size )
  {
    bpp = FreeRDPGetBytesPerPixel(clear->format);
    oldPos = bpp * vBarEntry->size;
    diffSize = bpp * (vBarEntry->count - vBarEntry->size);
    vBarEntry->size = vBarEntry->count;
    tmp = (BYTE *)chip::ArgParser::HelpOptions::HelpOptions(vBarEntry->pixels, vBarEntry->count, bpp, 0x20uLL);
    if ( !tmp )
      return 0;
    memset(&tmp[oldPos], 0, diffSize);
    vBarEntry->pixels = tmp;
  }
  return vBarEntry->pixels || !vBarEntry->size;
}