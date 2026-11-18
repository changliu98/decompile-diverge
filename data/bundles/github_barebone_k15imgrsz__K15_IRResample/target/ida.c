kir_result __cdecl K15_IRResample(kir_resize_context *p_Context)
{
  kir_u8 *transcodedSourcePixels; // [rsp+18h] [rbp-68h]
  kir_u8 *horizontalTempBuffer; // [rsp+20h] [rbp-60h]
  kir_u32 tempBufferSizeInBytes; // [rsp+2Ch] [rbp-54h]
  kir_pixel_format pixelFormat; // [rsp+48h] [rbp-38h]
  kir_wrap_mode wrapMode; // [rsp+4Ch] [rbp-34h]
  kir_u32 sourceWidth; // [rsp+50h] [rbp-30h]
  kir_u32 sourceHeight; // [rsp+54h] [rbp-2Ch]
  kir_u32 destinationWidth; // [rsp+5Ch] [rbp-24h]
  kir_u8 *destinationPixels; // [rsp+60h] [rbp-20h]
  kir_filter filter; // [rsp+74h] [rbp-Ch]

  filter = p_Context->filter;
  if ( p_Context->transcodedSourcePixels )
    transcodedSourcePixels = p_Context->transcodedSourcePixels;
  else
    transcodedSourcePixels = p_Context->sourcePixels;
  destinationPixels = p_Context->destinationPixels;
  destinationWidth = p_Context->destinationWidth;
  sourceHeight = p_Context->sourceHeight;
  sourceWidth = p_Context->sourceWidth;
  wrapMode = p_Context->wrapMode;
  pixelFormat = p_Context->destinationFormat;
  memset(destinationPixels, 0, kir_format_to_byte_lut[pixelFormat] * p_Context->destinationHeight * destinationWidth);
  if ( filter )
  {
    if ( filter == K15_IR_BILINEAR_FILTER || filter == K15_IR_BICUBIC_FILTER )
    {
      tempBufferSizeInBytes = kir_format_to_byte_lut[p_Context->destinationFormat] * sourceHeight * destinationWidth;
      horizontalTempBuffer = (kir_u8 *)malloc(tempBufferSizeInBytes);
      memset(horizontalTempBuffer, 0, tempBufferSizeInBytes);
      if ( filter == K15_IR_BILINEAR_FILTER )
      {
        K15_IRHorizontallySampleBilinear(
          transcodedSourcePixels,
          horizontalTempBuffer,
          sourceWidth,
          sourceHeight,
          destinationWidth,
          sourceHeight,
          pixelFormat,
          wrapMode);
        K15_IRHorizontallySampleBilinear(
          horizontalTempBuffer,
          destinationPixels,
          sourceHeight,
          destinationWidth,
          p_Context->destinationHeight,
          p_Context->destinationWidth,
          pixelFormat,
          wrapMode);
      }
      else
      {
        K15_IRHorizontallySampleBicubic(
          transcodedSourcePixels,
          horizontalTempBuffer,
          sourceWidth,
          sourceHeight,
          destinationWidth,
          sourceHeight,
          pixelFormat,
          wrapMode);
        K15_IRHorizontallySampleBicubic(
          horizontalTempBuffer,
          destinationPixels,
          sourceHeight,
          destinationWidth,
          p_Context->destinationHeight,
          p_Context->destinationWidth,
          pixelFormat,
          wrapMode);
      }
    }
  }
  else
  {
    K15_IRSampleNearestNeighbour(
      transcodedSourcePixels,
      p_Context->destinationPixels,
      p_Context->sourceWidth,
      p_Context->sourceHeight,
      p_Context->destinationWidth,
      p_Context->destinationHeight,
      p_Context->destinationFormat);
  }
  return 0;
}