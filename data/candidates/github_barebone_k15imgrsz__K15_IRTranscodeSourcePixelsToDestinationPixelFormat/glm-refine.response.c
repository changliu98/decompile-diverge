void __cdecl K15_IRTranscodeSourcePixelsToDestinationPixelFormat(kir_resize_context *p_Context)
{
    kir_u32 sourceWidth = p_Context->sourceWidth;
    kir_u32 sourceHeight = p_Context->sourceHeight;
    kir_u8 *sourcePixels = p_Context->sourcePixels;
    kir_pixel_format sourceFormat = p_Context->sourceFormat;
    kir_pixel_format destinationFormat = p_Context->destinationFormat;

    if (sourceFormat == destinationFormat)
        return;

    kir_u8 *transcodedSourcePixels = (kir_u8 *)malloc(kir_format_to_byte_lut[destinationFormat] * sourceHeight * sourceWidth);

    switch (sourceFormat)
    {
        case K15_IR_PIXEL_FORMAT_R8:
            switch (destinationFormat)
            {
                case K15_IR_PIXEL_FORMAT_R8A8:
                    K15_IRTranscodeFromR8ToR8G8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
                    break;
                case K15_IR_PIXEL_FORMAT_R8A8B8:
                    K15_IRTranscodeFromR8ToR8G8B8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
                    break;
                case K15_IR_PIXEL_FORMAT_R8A8B8A8:
                    K15_IRTranscodeFromR8ToR8G8B8A8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
                    break;
            }
            break;

        case K15_IR_PIXEL_FORMAT_R8A8:
            switch (destinationFormat)
            {
                case K15_IR_PIXEL_FORMAT_R8:
                    K15_IRTranscodeFromR8G8ToR8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
                    break;
                case K15_IR_PIXEL_FORMAT_R8A8B8:
                    K15_IRTranscodeFromR8G8ToR8G8B8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
                    break;
                case K15_IR_PIXEL_FORMAT_R8A8B8A8:
                    K15_IRTranscodeFromR8G8ToR8G8B8A8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
                    break;
            }
            break;

        case K15_IR_PIXEL_FORMAT_R8A8B8:
            switch (destinationFormat)
            {
                case K15_IR_PIXEL_FORMAT_R8:
                    K15_IRTranscodeFromR8G8B8ToR8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
                    break;
                case K15_IR_PIXEL_FORMAT_R8A8:
                    K15_IRTranscodeFromR8G8B8ToR8G8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
                    break;
                case K15_IR_PIXEL_FORMAT_R8A8B8A8:
                    K15_IRTranscodeFromR8G8B8ToR8G8B8A8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
                    break;
            }
            break;

        case K15_IR_PIXEL_FORMAT_R8A8B8A8:
            switch (destinationFormat)
            {
                case K15_IR_PIXEL_FORMAT_R8:
                    K15_IRTranscodeFromR8G8B8A8ToR8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
                    break;
                case K15_IR_PIXEL_FORMAT_R8A8:
                    K15_IRTranscodeFromR8G8B8A8ToR8G8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
                    break;
                case K15_IR_PIXEL_FORMAT_R8A8B8:
                    K15_IRTranscodeFromR8G8B8A8ToR8G8B8(sourcePixels, transcodedSourcePixels, sourceWidth, sourceHeight);
                    break;
            }
            break;
    }

    p_Context->transcodedSourcePixels = transcodedSourcePixels;
}