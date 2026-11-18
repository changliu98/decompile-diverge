kir_result _K15_IRResample(kir_resize_context *p_Context)

{
  kir_filter kVar1;
  kir_u32 kVar2;
  kir_u32 kVar3;
  kir_u32 kVar4;
  kir_wrap_mode p_WrapMode;
  kir_pixel_format p_PixelFormat;
  kir_u8 *p_DestinationPixels;
  kir_u16 p_SourceWidth;
  uint uVar5;
  kir_u8 *p_DestinationPixels_00;
  kir_u8 *local_70;
  kir_u8 *horizontalTempBuffer;
  kir_u32 tempBufferSizeInBytes;
  kir_u32 bpp_1;
  kir_pixel_format format;
  kir_u32 tempHeight;
  kir_u32 tempWidth;
  kir_u32 destinationPixelDataSizeInBytes;
  int bpp;
  kir_pixel_format pixelFormat;
  kir_wrap_mode wrapMode;
  kir_u32 sourceWidth;
  kir_u32 sourceHeight;
  kir_u32 destinationHeight;
  kir_u32 destinationWidth;
  kir_u8 *destinationPixels;
  kir_u8 *sourcePixels;
  kir_u32 flags;
  kir_filter filter;
  kir_resize_context *p_Context_local;
  kir_u16 p_SourceHeight;
  kir_u16 p_DestinationWidth;
  
  kVar1 = p_Context->filter;
  if (p_Context->transcodedSourcePixels == (kir_u8 *)0x0) {
    local_70 = p_Context->sourcePixels;
  }
  else {
    local_70 = p_Context->transcodedSourcePixels;
  }
  p_DestinationPixels = p_Context->destinationPixels;
  kVar2 = p_Context->destinationWidth;
  kVar3 = p_Context->sourceHeight;
  kVar4 = p_Context->sourceWidth;
  p_WrapMode = p_Context->wrapMode;
  p_PixelFormat = p_Context->destinationFormat;
  memset(p_DestinationPixels,0,
         (ulong)(kVar2 * p_Context->destinationHeight *
                kir_format_to_byte_lut[p_Context->destinationFormat]));
  if (kVar1 == K15_IR_NEAREST_NEIGHBOUR_FILTER) {
    _K15_IRSampleNearestNeighbour
              (local_70,p_Context->destinationPixels,p_Context->sourceWidth,p_Context->sourceHeight,
               p_Context->destinationWidth,p_Context->destinationHeight,p_Context->destinationFormat
              );
  }
  else if ((kVar1 == K15_IR_BILINEAR_FILTER) || (kVar1 == K15_IR_BICUBIC_FILTER)) {
    uVar5 = kVar2 * kVar3 * kir_format_to_byte_lut[p_Context->destinationFormat];
    p_DestinationPixels_00 = malloc((ulong)uVar5);
    memset(p_DestinationPixels_00,0,(ulong)uVar5);
    p_SourceWidth = (kir_u16)kVar4;
    p_SourceHeight = (kir_u16)kVar3;
    p_DestinationWidth = (kir_u16)kVar2;
    if (kVar1 == K15_IR_BILINEAR_FILTER) {
      _K15_IRHorizontallySampleBilinear
                (local_70,p_DestinationPixels_00,p_SourceWidth,p_SourceHeight,p_DestinationWidth,
                 p_SourceHeight,p_PixelFormat,p_WrapMode);
      _K15_IRHorizontallySampleBilinear
                (p_DestinationPixels_00,p_DestinationPixels,p_SourceHeight,p_DestinationWidth,
                 (kir_u16)p_Context->destinationHeight,(kir_u16)p_Context->destinationWidth,
                 p_PixelFormat,p_WrapMode);
    }
    else if (kVar1 == K15_IR_BICUBIC_FILTER) {
      _K15_IRHorizontallySampleBicubic
                (local_70,p_DestinationPixels_00,p_SourceWidth,p_SourceHeight,p_DestinationWidth,
                 p_SourceHeight,p_PixelFormat,p_WrapMode);
      _K15_IRHorizontallySampleBicubic
                (p_DestinationPixels_00,p_DestinationPixels,p_SourceHeight,p_DestinationWidth,
                 (kir_u16)p_Context->destinationHeight,(kir_u16)p_Context->destinationWidth,
                 p_PixelFormat,p_WrapMode);
    }
  }
  return K15_IR_RESULT_SUCCESS;
}