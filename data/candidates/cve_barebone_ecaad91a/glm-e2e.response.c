int clear_decompress_subcodecs_data(void* context, void* stream, uint32_t size, uint32_t totalWidth, uint32_t totalHeight,
                                    void* pDstData, uint32_t DstFormat, int nDstStep, int nXDst, int nYDst,
                                    uint32_t nXSrc, uint32_t nYSrc, uint32_t nWidth, uint32_t nHeight)
{
    uint32_t offset = 0;

    if (!Stream_CheckAndLogRequiredLength("clear_decompress_subcodecs_data", stream, size))
        return 0;

    while (offset < size)
    {
        if (!Stream_CheckAndLogRequiredLength("clear_decompress_subcodecs_data", stream, 13))
            return 0;

        uint16_t xDst = Stream_Get_UINT16(stream);
        uint16_t yDst = Stream_Get_UINT16(stream);
        uint16_t width = Stream_Get_UINT16(stream);
        uint16_t height = Stream_Get_UINT16(stream);
        uint32_t bitmapDataSize = Stream_Get_UINT32(stream);
        uint8_t codecType = Stream_Get_UINT8(stream);

        offset += 13;

        if (!Stream_CheckAndLogRequiredLength("clear_decompress_subcodecs_data", stream, bitmapDataSize))
            return 0;

        int nXDstRect = nXDst + xDst;
        int nYDstRect = nYDst + yDst;

        if ((uint64_t)nXDstRect + width > totalWidth)
            return 0;
        if ((uint64_t)nYDstRect + height > totalHeight)
            return 0;
        if ((uint64_t)xDst + width > totalWidth)
            return 0;
        if ((uint64_t)yDst + height > totalHeight)
            return 0;

        if (!clear_resize_buffer(context, width, height))
            return 0;

        if (codecType == 0)
        {
            uint32_t bpp = FreeRDPGetBytesPerPixel(0x18020888);
            uint32_t srcSize = bpp * width;
            uint64_t expectedSize = (uint64_t)srcSize * height;

            if (bitmapDataSize != expectedSize)
                return 0;

            void* pSrcData = Stream_Pointer(stream);
            if (!convert_color(pDstData, DstFormat, nDstStep, nXDstRect, nYDstRect, width, height,
                               pSrcData, 0x18020888, srcSize, nXSrc, nYSrc, nWidth, nHeight))
                return 0;

            Stream_Seek(stream, bitmapDataSize);
        }
        else if (codecType == 1)
        {
            // Assuming context struct has nscodec pointer at offset 0x8
            void* nscodec = *((void**)((char*)context + 0x8));
            if (!clear_decompress_nscodec(nscodec, width, height, stream, bitmapDataSize, pDstData,
                                          DstFormat, nDstStep, nXDstRect, nYDstRect))
                return 0;
        }
        else if (codecType == 2)
        {
            if (!clear_decompress_subcode_rlex(stream, bitmapDataSize, width, height, pDstData,
                                               DstFormat, nDstStep, nXDstRect, nYDstRect, nXSrc, nYSrc))
                return 0;
        }
        else
        {
            return 0;
        }

        offset += bitmapDataSize;
    }

    return 1;
}