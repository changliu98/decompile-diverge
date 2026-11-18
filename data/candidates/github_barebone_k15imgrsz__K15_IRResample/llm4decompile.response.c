kir_result _K15_IRResample(kir_resize_context *p_Context)
{
    kir_u8 *sourcePixels = p_Context->transcodedSourcePixels ? p_Context->transcodedSourcePixels : p_Context->sourcePixels;
    kir_u8 *destinationPixels = p_Context->destinationPixels;
    kir_u32 sourceWidth = p_Context->sourceWidth;
    kir_u32 sourceHeight = p_Context->sourceHeight;
    kir_u32 destinationWidth = p_Context->destinationWidth;
    kir_u32 destinationHeight = p_Context->destinationHeight;
    kir_filter filter = p_Context->filter;
    kir_wrap_mode wrapMode = p_Context->wrapMode;
    kir_pixel_format pixelFormat = p_Context->destinationFormat;
    kir_u32 destinationPixelDataSizeInBytes = destinationWidth * destinationHeight * kir_format_to_byte_lut[p_Context->destinationFormat];

    memset(destinationPixels, 0, destinationPixelDataSizeInBytes);

    if (filter == K15_IR_NEAREST_NEIGHBOUR_FILTER)
    {
        _K15_IRSampleNearestNeighbour(sourcePixels, destinationPixels, sourceWidth, sourceHeight, destinationWidth, destinationHeight, pixelFormat);
    }
    else if (filter == K15_IR_BILINEAR_FILTER || filter == K15_IR_BICUBIC_FILTER)
    {
        kir_u8 *horizontalTempBuffer = malloc(destinationPixelDataSizeInBytes);
        memset(horizontalTempBuffer, 0, destinationPixelDataSizeInBytes);

        if (filter == K15_IR_BILINEAR_FILTER)
        {
            _K15_IRHorizontallySampleBilinear(sourcePixels, horizontalTempBuffer, sourceWidth, sourceHeight, destinationWidth, sourceHeight, pixelFormat, wrapMode);
            _K15_IRHorizontallySampleBilinear(horizontalTempBuffer, destinationPixels, sourceHeight, destinationWidth, destinationHeight, destinationWidth, pixelFormat, wrapMode);
        }
        else if (filter == K15_IR_BICUBIC_FILTER)
        {
            _K15_IRHorizontallySampleBicubic(sourcePixels, horizontalTempBuffer, sourceWidth, sourceHeight, destinationWidth, sourceHeight, pixelFormat, wrapMode);
            _K15_IRHorizontallySampleBicubic(horizontalTempBuffer, destinationPixels, sourceHeight, destinationWidth, destinationHeight, destinationWidth, pixelFormat, wrapMode);
        }
    }

    return K15_IR_RESULT_SUCCESS;
}