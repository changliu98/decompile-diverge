void _K15_IRTranscodeSourcePixelsToDestinationPixelFormat(kir_resize_context *p_Context)

{
  kir_u32 p_Width;
  kir_u32 p_Height;
  kir_pixel_format kVar1;
  kir_pixel_format kVar2;
  kir_u8 *p_InputPixels;
  kir_u8 *p_OutputPixels;
  kir_u8 *transcodedSourcePixels;
  kir_pixel_format destinationFormat;
  kir_pixel_format sourceFormat;
  kir_u8 *sourcePixels;
  kir_u32 sourceHeight;
  kir_u32 sourceWidth;
  kir_resize_context *p_Context_local;
  
  p_Width = p_Context->sourceWidth;
  p_Height = p_Context->sourceHeight;
  p_InputPixels = p_Context->sourcePixels;
  kVar1 = p_Context->sourceFormat;
  kVar2 = p_Context->destinationFormat;
  if (kVar1 != kVar2) {
    p_OutputPixels = malloc((ulong)(p_Width * p_Height * kir_format_to_byte_lut[kVar2]));
    if ((kVar1 == K15_IR_PIXEL_FORMAT_R8) && (kVar2 == K15_IR_PIXEL_FORMAT_R8A8)) {
      _K15_IRTranscodeFromR8ToR8G8(p_InputPixels,p_OutputPixels,p_Width,p_Height);
    }
    else if ((kVar1 == K15_IR_PIXEL_FORMAT_R8) && (kVar2 == K15_IR_PIXEL_FORMAT_R8A8B8)) {
      _K15_IRTranscodeFromR8ToR8G8B8(p_InputPixels,p_OutputPixels,p_Width,p_Height);
    }
    else if ((kVar1 == K15_IR_PIXEL_FORMAT_R8) && (kVar2 == K15_IR_PIXEL_FORMAT_R8A8B8A8)) {
      _K15_IRTranscodeFromR8ToR8G8B8A8(p_InputPixels,p_OutputPixels,p_Width,p_Height);
    }
    else if ((kVar1 == K15_IR_PIXEL_FORMAT_R8A8) && (kVar2 == K15_IR_PIXEL_FORMAT_R8)) {
      _K15_IRTranscodeFromR8G8ToR8(p_InputPixels,p_OutputPixels,p_Width,p_Height);
    }
    else if ((kVar1 == K15_IR_PIXEL_FORMAT_R8A8) && (kVar2 == K15_IR_PIXEL_FORMAT_R8A8B8)) {
      _K15_IRTranscodeFromR8G8ToR8G8B8(p_InputPixels,p_OutputPixels,p_Width,p_Height);
    }
    else if ((kVar1 == K15_IR_PIXEL_FORMAT_R8A8) && (kVar2 == K15_IR_PIXEL_FORMAT_R8A8B8A8)) {
      _K15_IRTranscodeFromR8G8ToR8G8B8A8(p_InputPixels,p_OutputPixels,p_Width,p_Height);
    }
    else if ((kVar1 == K15_IR_PIXEL_FORMAT_R8A8B8) && (kVar2 == K15_IR_PIXEL_FORMAT_R8)) {
      _K15_IRTranscodeFromR8G8B8ToR8(p_InputPixels,p_OutputPixels,p_Width,p_Height);
    }
    else if ((kVar1 == K15_IR_PIXEL_FORMAT_R8A8B8) && (kVar2 == K15_IR_PIXEL_FORMAT_R8A8)) {
      _K15_IRTranscodeFromR8G8B8ToR8G8(p_InputPixels,p_OutputPixels,p_Width,p_Height);
    }
    else if ((kVar1 == K15_IR_PIXEL_FORMAT_R8A8B8) && (kVar2 == K15_IR_PIXEL_FORMAT_R8A8B8A8)) {
      _K15_IRTranscodeFromR8G8B8ToR8G8B8A8(p_InputPixels,p_OutputPixels,p_Width,p_Height);
    }
    else if ((kVar1 == K15_IR_PIXEL_FORMAT_R8A8B8A8) && (kVar2 == K15_IR_PIXEL_FORMAT_R8)) {
      _K15_IRTranscodeFromR8G8B8A8ToR8(p_InputPixels,p_OutputPixels,p_Width,p_Height);
    }
    else if ((kVar1 == K15_IR_PIXEL_FORMAT_R8A8B8A8) && (kVar2 == K15_IR_PIXEL_FORMAT_R8A8)) {
      _K15_IRTranscodeFromR8G8B8A8ToR8G8(p_InputPixels,p_OutputPixels,p_Width,p_Height);
    }
    else if ((kVar1 == K15_IR_PIXEL_FORMAT_R8A8B8A8) && (kVar2 == K15_IR_PIXEL_FORMAT_R8A8B8)) {
      _K15_IRTranscodeFromR8G8B8A8ToR8G8B8(p_InputPixels,p_OutputPixels,p_Width,p_Height);
    }
    p_Context->transcodedSourcePixels = p_OutputPixels;
  }
  return;
}