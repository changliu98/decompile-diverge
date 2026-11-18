BOOL __cdecl clear_decompress_subcodecs_data(
        CLEAR_CONTEXT *clear,
        wStream *s,
        UINT32 subcodecByteCount,
        UINT32 nWidth,
        UINT32 nHeight,
        BYTE *pDstData,
        UINT32 DstFormat,
        UINT32 nDstStep,
        UINT32 nXDst,
        UINT32 nYDst,
        UINT32 nDstWidth,
        UINT32 nDstHeight,
        const gdiPalette *palette)
{
    UINT32 suboffset = 0;

    // Validate the total required length for the subcodec data
    if (!Stream_CheckAndLogRequiredLength("codec.clear", s, subcodecByteCount))
        return FALSE;

    while (suboffset < subcodecByteCount)
    {
        UINT16 xStart, yStart, width, height;
        UINT32 bitmapDataByteCount;
        UINT8 subcodecId;
        UINT32 nXDstRel, nYDstRel;
        UINT32 nSrcStep;
        const BYTE *src;

        // Each subcodec entry has a 13-byte header
        if (!Stream_CheckAndLogRequiredLength("codec.clear", s, 13))
            return FALSE;

        xStart = Stream_Get_UINT16(s);
        yStart = Stream_Get_UINT16(s);
        width = Stream_Get_UINT16(s);
        height = Stream_Get_UINT16(s);
        bitmapDataByteCount = Stream_Get_UINT32(s);
        subcodecId = Stream_Get_UINT8(s);

        // Validate the payload length
        if (!Stream_CheckAndLogRequiredLength("codec.clear", s, bitmapDataByteCount))
            return FALSE;

        nXDstRel = xStart + nXDst;
        nYDstRel = yStart + nYDst;

        // Bounds checking to prevent buffer overflows
        if ((UINT64)width + nXDstRel > nWidth || (UINT64)height + nYDstRel > nHeight)
            return FALSE;

        if ((UINT64)width + xStart > nWidth || (UINT64)height + yStart > nHeight)
            return FALSE;

        if (!clear_resize_buffer(clear, width, height))
            return FALSE;

        // Dispatch to the appropriate decompression handler based on subcodec ID
        switch (subcodecId)
        {
            case 0: // Raw format
                nSrcStep = FreeRDPGetBytesPerPixel(0x18020888u) * width;
                if (bitmapDataByteCount != (UINT64)height * nSrcStep)
                    return FALSE;

                src = (const BYTE *)Stream_Pointer(s);
                if (!convert_color(
                        pDstData, nDstStep, DstFormat, nXDstRel, nYDstRel,
                        width, height, src, nSrcStep, 0x18020888u,
                        nDstWidth, nDstHeight, palette))
                {
                    return FALSE;
                }
                Stream_Seek(s, bitmapDataByteCount);
                break;

            case 1: // NSCodec
                if (!clear_decompress_nscodec(
                        clear->nsc, width, height, s, bitmapDataByteCount,
                        pDstData, DstFormat, nDstStep, nXDstRel, nYDstRel))
                {
                    return FALSE;
                }
                break;

            case 2: // RLEX
                if (!clear_decompress_subcode_rlex(
                        s, bitmapDataByteCount, width, height,
                        pDstData, DstFormat, nDstStep, nXDstRel, nYDstRel,
                        nDstWidth, nDstHeight))
                {
                    return FALSE;
                }
                break;

            default:
                return FALSE;
        }

        // Advance the offset by header size (13 bytes) + payload size
        suboffset += 13 + bitmapDataByteCount;
    }

    return TRUE;
}