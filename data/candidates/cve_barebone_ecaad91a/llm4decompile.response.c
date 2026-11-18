BOOL
clear_decompress_subcodecs_data(CLEAR_CONTEXT *clear, wStream *s, UINT32 subcodecByteCount,
                                UINT32 nWidth, UINT32 nHeight, BYTE *pDstData, UINT32 DstFormat,
                                UINT32 nDstStep, UINT32 nXDst, UINT32 nYDst, UINT32 nDstWidth,
                                UINT32 nDstHeight, gdiPalette *palette)
{
    UINT32 suboffset;
    UINT16 xStart, yStart, width, height;
    UINT32 bitmapDataByteCount;
    BYTE subcodecId;

    if (!Stream_CheckAndLogRequiredLength("codec.clear", s, subcodecByteCount))
        return 0;

    for (suboffset = 0; suboffset < subcodecByteCount; suboffset += 13 + bitmapDataByteCount)
    {
        if (!Stream_CheckAndLogRequiredLength("codec.clear", s, 13))
            return 0;

        xStart = Stream_Get_UINT16(s);
        yStart = Stream_Get_UINT16(s);
        width = Stream_Get_UINT16(s);
        height = Stream_Get_UINT16(s);
        bitmapDataByteCount = Stream_Get_UINT32(s);
        subcodecId = Stream_Get_UINT8(s);

        if (!Stream_CheckAndLogRequiredLength("codec.clear", s, bitmapDataByteCount))
            return 0;

        if ((xStart + width > nWidth) || (yStart + height > nHeight))
            return 0;

        if ((xStart + width > nWidth) || (yStart + height > nHeight))
            return 0;

        if (!clear_resize_buffer(clear, width, height))
            return 0;

        switch (subcodecId)
        {
            case 0:
            {
                UINT32 srcStep;
                BYTE *src;

                srcStep = width * FreeRDPGetBytesPerPixel(0x18020888);

                if (bitmapDataByteCount != srcStep * height)
                    return 0;

                src = Stream_Pointer(s);

                if (!convert_color(pDstData, nDstStep, DstFormat, xStart + nXDst, yStart + nYDst,
                                   width, height, src, srcStep, 0x18020888, nDstWidth, nDstHeight, palette))
                    return 0;

                Stream_Seek(s, bitmapDataByteCount);
                break;
            }

            case 1:
                if (!clear_decompress_nscodec(clear->nsc, width, height, s, bitmapDataByteCount,
                                              pDstData, DstFormat, nDstStep, xStart + nXDst, yStart + nYDst))
                    return 0;
                break;

            case 2:
                if (!clear_decompress_subcode_rlex(s, bitmapDataByteCount, width, height, pDstData,
                                                   DstFormat, nDstStep, xStart + nXDst, yStart + nYDst,
                                                   nDstWidth, nDstHeight))
                    return 0;
                break;

            default:
                return 0;
        }
    }

    return 1;
}