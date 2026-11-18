kir_result __cdecl K15_IRResample(kir_resize_context *p_Context)
{
    kir_u8 *transcodedSourcePixels;
    kir_u8 *horizontalTempBuffer;
    kir_u32 tempBufferSizeInBytes;
    kir_pixel_format pixelFormat;
    kir_wrap_mode wrapMode;
    kir_u32 sourceWidth;
    kir_u32 sourceHeight;
    kir_u32 destinationWidth;
    kir_u32 destinationHeight;
    kir_u8 *destinationPixels;
    kir_filter filter;

    // Load context into local variables
    filter = p_Context->filter;
    transcodedSourcePixels = p_Context->transcodedSourcePixels ? p_Context->transcodedSourcePixels : p_Context->sourcePixels;
    destinationPixels = p_Context->destinationPixels;
    destinationWidth = p_Context->destinationWidth;
    destinationHeight = p_Context->destinationHeight;
    sourceHeight = p_Context->sourceHeight;
    sourceWidth = p_Context->sourceWidth;
    wrapMode = p_Context->wrapMode;
    pixelFormat = p_Context->destinationFormat;

    // Clear destination buffer
    memset(destinationPixels, 0, kir_format_to_byte_lut[pixelFormat] * destinationHeight * destinationWidth);

    if (filter == K15_IR_NEAREST_NEIGHBOUR) // Assuming 0 corresponds to nearest neighbour
    {
        K15_IRSampleNearestNeighbour(
            transcodedSourcePixels,
            destinationPixels,
            sourceWidth,
            sourceHeight,
            destinationWidth,
            destinationHeight,
            pixelFormat);
    }
    else if (filter == K15_IR_BILINEAR_FILTER || filter == K15_IR_BICUBIC_FILTER)
    {
        // Allocate intermediate horizontal sampling buffer
        tempBufferSizeInBytes = kir_format_to_byte_lut[pixelFormat] * sourceHeight * destinationWidth;
        horizontalTempBuffer = (kir_u8 *)malloc(tempBufferSizeInBytes);
        memset(horizontalTempBuffer, 0, tempBufferSizeInBytes);

        if (filter == K15_IR_BILINEAR_FILTER)
        {
            // Pass 1: Horizontal resampling (source dimensions -> intermediate width)
            K15_IRHorizontallySampleBilinear(
                transcodedSourcePixels,
                horizontalTempBuffer,
                sourceWidth,
                sourceHeight,
                destinationWidth,
                sourceHeight,
                pixelFormat,
                wrapMode);

            // Pass 2: Vertical resampling (intermediate height -> destination dimensions)
            K15_IRHorizontallySampleBilinear(
                horizontalTempBuffer,
                destinationPixels,
                sourceHeight,
                destinationWidth,
                destinationHeight,
                destinationWidth,
                pixelFormat,
                wrapMode);
        }
        else // filter == K15_IR_BICUBIC_FILTER
        {
            // Pass 1: Horizontal resampling (source dimensions -> intermediate width)
            K15_IRHorizontallySampleBicubic(
                transcodedSourcePixels,
                horizontalTempBuffer,
                sourceWidth,
                sourceHeight,
                destinationWidth,
                sourceHeight,
                pixelFormat,
                wrapMode);

            // Pass 2: Vertical resampling (intermediate height -> destination dimensions)
            K15_IRHorizontallySampleBicubic(
                horizontalTempBuffer,
                destinationPixels,
                sourceHeight,
                destinationWidth,
                destinationHeight,
                destinationWidth,
                pixelFormat,
                wrapMode);
        }
    }

    return 0;
}