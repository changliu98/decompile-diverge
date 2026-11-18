BOOL
gdi_Bitmap_Decompress(rdpContext * context, rdpBitmap * bitmap, BYTE * pSrcData,
                      UINT32 DstWidth, UINT32 DstHeight, UINT32 bpp, UINT32 length, BOOL compressed, UINT32 codecId)
{
    rdpGdi *gdi;
    UINT32 SrcFormat;
    UINT32 SrcSize;
    UINT32 DstSize;
    UINT32 sbpp;
    UINT32 dbpp;
    UINT32 bpp_local;
    BYTE *pSrcData_local;
    rdpContext *context_local;
    rdpBitmap *bitmap_local;
    DstWidth;
    DstHeight;
    length;
    codecId;
    gdi = context->gdi;
    bitmap->compressed = 0;
    bitmap->format = gdi->dstFormat;
    bitmap->length = DstWidth * DstHeight * GetBytesPerPixel(bitmap->format);
    bitmap->data = (BYTE *) _aligned_malloc(bitmap->length, 16);
    if (bitmap->data == NULL)
    {
        return 0;
    }

    if (compressed)
    {
        if (bpp < 32)
        {
            if (!interleaved_decompress(context->codecs->interleaved, pSrcData, length,
                                        DstWidth, DstHeight, bpp, bitmap->data, bitmap->format,
                                        0, 0, 0, DstWidth, DstHeight, &gdi->palette))
            {
                return 0;
            }
        }
        else
        {
            if (!planar_decompress(context->codecs->planar, pSrcData, length,
                                   DstWidth, DstHeight, bitmap->data, bitmap->format,
                                   0, 0, 0, DstWidth, DstHeight, 1))
            {
                return 0;
            }
        }
    }
    else
    {
        SrcFormat = gdi_get_pixel_format(bpp);
        sbpp = GetBytesPerPixel(SrcFormat);
        dbpp = GetBytesPerPixel(bitmap->format);
        if (sbpp == 0 || dbpp == 0)
        {
            return 0;
        }
        SrcSize = length * sbpp;
        DstSize = bitmap->length * dbpp;
        if (SrcSize < DstSize)
        {
            return 0;
        }

        if (!freerdp_image_copy(bitmap->data, bitmap->format,
                                0, 0, 0, DstWidth, DstHeight,
                                pSrcData, SrcFormat,
                                0, 0, 0, &gdi->palette, 1))
        {
            return 0;
        }
    }
    return 1;
}