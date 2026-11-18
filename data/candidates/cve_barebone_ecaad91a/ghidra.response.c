BOOL clear_decompress_subcodecs_data
               (CLEAR_CONTEXT *clear,wStream *s,UINT32 subcodecByteCount,UINT32 nWidth,
               UINT32 nHeight,BYTE *pDstData,UINT32 DstFormat,UINT32 nDstStep,UINT32 nXDst,
               UINT32 nYDst,UINT32 nDstWidth,UINT32 nDstHeight,gdiPalette *palette)

{
  UINT8 UVar1;
  UINT16 UVar2;
  UINT16 UVar3;
  UINT16 UVar4;
  UINT16 UVar5;
  BOOL BVar6;
  UINT32 bitmapDataByteCount_00;
  uint nXDst_00;
  uint nYDst_00;
  UINT32 UVar7;
  BYTE *src;
  size_t nSrcSize;
  UINT32 nSrcStep;
  UINT32 nYDstRel;
  UINT32 nXDstRel;
  UINT8 subcodecId;
  UINT32 bitmapDataByteCount;
  UINT16 height;
  UINT16 width;
  UINT16 yStart;
  UINT16 xStart;
  UINT32 suboffset;
  BYTE *pDstData_local;
  UINT32 nHeight_local;
  UINT32 nWidth_local;
  UINT32 subcodecByteCount_local;
  wStream *s_local;
  CLEAR_CONTEXT *clear_local;
  BOOL local_24;
  
  suboffset = 0;
  BVar6 = Stream_CheckAndLogRequiredLength("codec.clear",s,(ulong)subcodecByteCount);
  if (BVar6 == 0) {
    local_24 = 0;
  }
  else {
    for (; suboffset < subcodecByteCount; suboffset = bitmapDataByteCount_00 + suboffset + 0xd) {
      BVar6 = Stream_CheckAndLogRequiredLength("codec.clear",s,0xd);
      if (BVar6 == 0) {
        return 0;
      }
      UVar2 = Stream_Get_UINT16(s);
      UVar3 = Stream_Get_UINT16(s);
      UVar4 = Stream_Get_UINT16(s);
      UVar5 = Stream_Get_UINT16(s);
      bitmapDataByteCount_00 = Stream_Get_UINT32(s);
      UVar1 = Stream_Get_UINT8(s);
      BVar6 = Stream_CheckAndLogRequiredLength("codec.clear",s,(ulong)bitmapDataByteCount_00);
      if (BVar6 == 0) {
        return 0;
      }
      nXDst_00 = nXDst + UVar2;
      nYDst_00 = nYDst + UVar3;
      if ((ulong)nWidth < (ulong)nXDst_00 + (ulong)UVar4) {
        return 0;
      }
      if ((ulong)nHeight < (ulong)nYDst_00 + (ulong)UVar5) {
        return 0;
      }
      if (nWidth < (uint)UVar2 + (uint)UVar4) {
        return 0;
      }
      if (nHeight < (uint)UVar3 + (uint)UVar5) {
        return 0;
      }
      BVar6 = clear_resize_buffer(clear,(uint)UVar4,(uint)UVar5);
      if (BVar6 == 0) {
        return 0;
      }
      if (UVar1 == '\0') {
        UVar7 = FreeRDPGetBytesPerPixel(0x18020888);
        if ((ulong)bitmapDataByteCount_00 != (ulong)(UVar4 * UVar7) * (ulong)UVar5) {
          return 0;
        }
        src = Stream_Pointer(s);
        BVar6 = convert_color(pDstData,nDstStep,DstFormat,nXDst_00,nYDst_00,(uint)UVar4,(uint)UVar5,
                              src,UVar4 * UVar7,0x18020888,nDstWidth,nDstHeight,palette);
        if (BVar6 == 0) {
          return 0;
        }
        Stream_Seek(s,(ulong)bitmapDataByteCount_00);
      }
      else if (UVar1 == '\x01') {
        BVar6 = clear_decompress_nscodec
                          (clear->nsc,(uint)UVar4,(uint)UVar5,s,bitmapDataByteCount_00,pDstData,
                           DstFormat,nDstStep,nXDst_00,nYDst_00);
        if (BVar6 == 0) {
          return 0;
        }
      }
      else {
        if (UVar1 != '\x02') {
          return 0;
        }
        BVar6 = clear_decompress_subcode_rlex
                          (s,bitmapDataByteCount_00,(uint)UVar4,(uint)UVar5,pDstData,DstFormat,
                           nDstStep,nXDst_00,nYDst_00,nDstWidth,nDstHeight);
        if (BVar6 == 0) {
          return 0;
        }
      }
    }
    local_24 = 1;
  }
  return local_24;
}