void _K15_IRTranscodeSourcePixelsToDestinationPixelFormat(struct _kir_resize_context *p_Context)
{
  struct _kir_u32 sourceWidth = p_Context->sourceWidth;
  struct _kir_u32 sourceHeight = p_Context->sourceHeight;
  struct _kir_u8 *sourcePixels = p_Context->sourcePixels;
  struct _kir_pixel_format sourceFormat = p_Context->sourceFormat;
  struct _kir_pixel_format destinationFormat = p_Context->destinationFormat;
  if (sourceFormat != destinationFormat)
  {
    struct _kir_u8 *transcodedSourcePixels = (kir_u8 *)malloc(sourceWidth * sourceHeight * kir_format_to_byte_lut[destinationFormat]);
    if (sourceFormat == K15_IR_PIXEL_FORMAT_R8)
    {
      if (destinationFormat == K15_IR_PIXEL_FORMAT_R8A8)
      {
        K15_IRTranscodeFromR8ToR8G8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
      }
      else if (destinationFormat == K15_IR_PIXEL_FORMAT_R8A8B8)
      {
        K15_IRTranscodeFromR8ToR8G8B8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
      }
      else if (destinationFormat == K15_IR_PIXEL_FORMAT_R8A8B8A8)
      {
        K15_IRTranscodeFromR8ToR8G8B8A8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
      }
    }
    else if (sourceFormat == K15_IR_PIXEL_FORMAT_R8A8)
    {
      if (destinationFormat == K15_IR_PIXEL_FORMAT_R8)
      {
        K15_IRTranscodeFromR8G8ToR8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
      }
      else if (destinationFormat == K15_IR_PIXEL_FORMAT_R8A8B8)
      {
        K15_IRTranscodeFromR8G8ToR8G8B8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
      }
      else if (destinationFormat == K15_IR_PIXEL_FORMAT_R8A8B8A8)
      {
        K15_IRTranscodeFromR8G8ToR8G8B8A8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
      }
    }
    else if (sourceFormat == K15_IR_PIXEL_FORMAT_R8A8B8)
    {
      if (destinationFormat == K15_IR_PIXEL_FORMAT_R8)
      {
        K15_IRTranscodeFromR8G8B8ToR8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
      }
      else if (destinationFormat == K15_IR_PIXEL_FORMAT_R8A8)
      {
        K15_IRTranscodeFromR8G8B8ToR8G8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
      }
      else if (destinationFormat == K15_IR_PIXEL_FORMAT_R8A8B8A8)
      {
        K15_IRTranscodeFromR8G8B8ToR8G8B8A8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
      }
    }
    else if (sourceFormat == K15_IR_PIXEL_FORMAT_R8A8B8A8)
    {
      if (destinationFormat == K15_IR_PIXEL_FORMAT_R8)
      {
        K15_IRTranscodeFromR8G8B8A8ToR8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
      }
      else if (destinationFormat == K15_IR_PIXEL_FORMAT_R8A8)
      {
        K15_IRTranscodeFromR8G8B8A8ToR8G8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
      }
      else if (destinationFormat == K15_IR_PIXEL_FORMAT_R8A8B8)
      {
        K15_IRTranscodeFromR8G8B8A8ToR8G8B8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
      }
      else if (destinationFormat == K15_IR_PIXEL_FORMAT_R8A8B8A8)
      {
      }
    }
    p_Context->transcodedSourcePixels = transcodedSourcePixels;
  }
}