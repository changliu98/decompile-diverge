void __cdecl K15_IRTranscodeSourcePixelsToDestinationPixelFormat(kir_resize_context *p_Context)
{
  kir_u8 *transcodedSourcePixels; // [rsp+8h] [rbp-28h]
  kir_pixel_format destinationFormat; // [rsp+10h] [rbp-20h]
  kir_pixel_format sourceFormat; // [rsp+14h] [rbp-1Ch]
  kir_u8 *sourcePixels; // [rsp+18h] [rbp-18h]
  kir_u32 sourceHeight; // [rsp+20h] [rbp-10h]
  kir_u32 sourceWidth; // [rsp+24h] [rbp-Ch]

  sourceWidth = p_Context->sourceWidth;
  sourceHeight = p_Context->sourceHeight;
  sourcePixels = p_Context->sourcePixels;
  sourceFormat = p_Context->sourceFormat;
  destinationFormat = p_Context->destinationFormat;
  if ( sourceFormat != destinationFormat )
  {
    transcodedSourcePixels = (kir_u8 *)malloc(kir_format_to_byte_lut[destinationFormat] * sourceHeight * sourceWidth);
    if ( sourceFormat || destinationFormat != K15_IR_PIXEL_FORMAT_R8A8 )
    {
      if ( sourceFormat || destinationFormat != K15_IR_PIXEL_FORMAT_R8A8B8 )
      {
        if ( sourceFormat || destinationFormat != K15_IR_PIXEL_FORMAT_R8A8B8A8 )
        {
          if ( sourceFormat != K15_IR_PIXEL_FORMAT_R8A8 || destinationFormat )
          {
            if ( sourceFormat == K15_IR_PIXEL_FORMAT_R8A8 && destinationFormat == K15_IR_PIXEL_FORMAT_R8A8B8 )
            {
              K15_IRTranscodeFromR8G8ToR8G8B8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
            }
            else if ( sourceFormat == K15_IR_PIXEL_FORMAT_R8A8 && destinationFormat == K15_IR_PIXEL_FORMAT_R8A8B8A8 )
            {
              K15_IRTranscodeFromR8G8ToR8G8B8A8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
            }
            else if ( sourceFormat != K15_IR_PIXEL_FORMAT_R8A8B8 || destinationFormat )
            {
              if ( sourceFormat == K15_IR_PIXEL_FORMAT_R8A8B8 && destinationFormat == K15_IR_PIXEL_FORMAT_R8A8 )
              {
                K15_IRTranscodeFromR8G8B8ToR8G8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
              }
              else if ( sourceFormat == K15_IR_PIXEL_FORMAT_R8A8B8 && destinationFormat == K15_IR_PIXEL_FORMAT_R8A8B8A8 )
              {
                K15_IRTranscodeFromR8G8B8ToR8G8B8A8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
              }
              else if ( sourceFormat != K15_IR_PIXEL_FORMAT_R8A8B8A8 || destinationFormat )
              {
                if ( sourceFormat == K15_IR_PIXEL_FORMAT_R8A8B8A8 && destinationFormat == K15_IR_PIXEL_FORMAT_R8A8 )
                {
                  K15_IRTranscodeFromR8G8B8A8ToR8G8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
                }
                else if ( sourceFormat == K15_IR_PIXEL_FORMAT_R8A8B8A8
                       && destinationFormat == K15_IR_PIXEL_FORMAT_R8A8B8 )
                {
                  K15_IRTranscodeFromR8G8B8A8ToR8G8B8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
                }
              }
              else
              {
                K15_IRTranscodeFromR8G8B8A8ToR8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
              }
            }
            else
            {
              K15_IRTranscodeFromR8G8B8ToR8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
            }
          }
          else
          {
            K15_IRTranscodeFromR8G8ToR8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
          }
        }
        else
        {
          K15_IRTranscodeFromR8ToR8G8B8A8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
        }
      }
      else
      {
        K15_IRTranscodeFromR8ToR8G8B8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
      }
    }
    else
    {
      K15_IRTranscodeFromR8ToR8G8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
    }
    p_Context->transcodedSourcePixels = transcodedSourcePixels;
  }
}