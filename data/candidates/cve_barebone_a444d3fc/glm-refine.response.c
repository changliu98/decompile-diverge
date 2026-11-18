BOOL __cdecl gdi_Bitmap_Decompress(
        rdpContext *context,
        rdpBitmap *bitmap,
        const BYTE *pSrcData,
        UINT32 DstWidth,
        UINT32 DstHeight,
        UINT32 bpp,
        UINT32 length,
        BOOL compressed,
        UINT32 codecId)
{
    rdpGdi *gdi;
    UINT32 SrcFormat;
    size_t sbpp, dbpp;

    if (!context || !context->gdi || !bitmap)
        return 0;

    gdi = context->gdi;
    
    // Initialize bitmap properties
    bitmap->compressed = FALSE;
    bitmap->format = gdi->dstFormat;
    bitmap->length = GetBytesPerPixel(bitmap->format) * DstHeight * DstWidth;
    bitmap->data = (BYTE *)aligned_malloc(bitmap->length, 16);
    
    if (!bitmap->data)
        return 0;

    if (compressed)
    {
        if (bpp >= 32)
        {
            if (!planar_decompress(
                    context->codecs->planar,
                    pSrcData, length,
                    DstWidth, DstHeight,
                    bitmap->data, bitmap->format,
                    0, 0, 0, DstWidth, DstHeight, 1))
                return 0;
        }
        else
        {
            if (!interleaved_decompress(
                    context->codecs->interleaved,
                    pSrcData, length,
                    DstWidth, DstHeight, bpp,
                    bitmap->data, bitmap->format,
                    0, 0, 0, DstWidth, DstHeight,
                    &gdi->palette))
                return 0;
        }
    }
    else
    {
        SrcFormat = gdi_get_pixel_format(bpp);
        sbpp = GetBytesPerPixel(SrcFormat);
        dbpp = GetBytesPerPixel(bitmap->format);
        
        if (!sbpp || !dbpp)
            return 0;
            
        if ((dbpp * length) / sbpp < bitmap->length)
            return 0;
            
        if (!freerdp_image_copy(
                bitmap->data, bitmap->format,
                0, 0, 0, DstWidth, DstHeight,
                pSrcData, SrcFormat,
                0, 0, 0, &gdi->palette, 1))
            return 0;
    }
    
    return 1;
}