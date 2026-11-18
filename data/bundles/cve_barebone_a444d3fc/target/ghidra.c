BOOL gdi_Bitmap_Decompress
               (rdpContext *context,rdpBitmap *bitmap,BYTE *pSrcData,UINT32 DstWidth,
               UINT32 DstHeight,UINT32 bpp,UINT32 length,BOOL compressed,UINT32 codecId)

{
  rdpGdi *prVar1;
  UINT32 UVar2;
  BOOL BVar3;
  UINT32 UVar4;
  UINT32 UVar5;
  BYTE *pBVar6;
  size_t dstSize;
  size_t dbpp;
  size_t sbpp;
  UINT32 SrcFormat;
  rdpGdi *gdi;
  UINT32 SrcSize;
  UINT32 bpp_local;
  UINT32 DstHeight_local;
  UINT32 DstWidth_local;
  BYTE *pSrcData_local;
  rdpBitmap *bitmap_local;
  rdpContext *context_local;
  
  prVar1 = context->gdi;
  bitmap->compressed = 0;
  bitmap->format = prVar1->dstFormat;
  UVar2 = GetBytesPerPixel(bitmap->format);
  bitmap->length = DstWidth * DstHeight * UVar2;
  pBVar6 = _aligned_malloc((ulong)bitmap->length,0x10);
  bitmap->data = pBVar6;
  if (bitmap->data == (BYTE *)0x0) {
    return 0;
  }
  if (compressed == 0) {
    UVar2 = gdi_get_pixel_format(bpp);
    UVar4 = GetBytesPerPixel(UVar2);
    UVar5 = GetBytesPerPixel(bitmap->format);
    if (((ulong)UVar4 == 0) || ((ulong)UVar5 == 0)) {
      return 0;
    }
    if (((ulong)length * (ulong)UVar5) / (ulong)UVar4 < (ulong)bitmap->length) {
      return 0;
    }
    BVar3 = freerdp_image_copy(bitmap->data,bitmap->format,0,0,0,DstWidth,DstHeight,pSrcData,UVar2,0
                               ,0,0,&prVar1->palette,1);
    if (BVar3 == 0) {
      return 0;
    }
  }
  else if (bpp < 0x20) {
    BVar3 = interleaved_decompress
                      (context->codecs->interleaved,pSrcData,length,DstWidth,DstHeight,bpp,
                       bitmap->data,bitmap->format,0,0,0,DstWidth,DstHeight,&prVar1->palette);
    if (BVar3 == 0) {
      return 0;
    }
  }
  else {
    BVar3 = planar_decompress(context->codecs->planar,pSrcData,length,DstWidth,DstHeight,
                              bitmap->data,bitmap->format,0,0,0,DstWidth,DstHeight,1);
    if (BVar3 == 0) {
      return 0;
    }
  }
  return 1;
}