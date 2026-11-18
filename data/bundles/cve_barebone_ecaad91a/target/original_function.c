static BOOL clear_decompress_subcodecs_data(CLEAR_CONTEXT* WINPR_RESTRICT clear,
                                            wStream* WINPR_RESTRICT s, UINT32 subcodecByteCount,
                                            UINT32 nWidth, UINT32 nHeight,
                                            BYTE* WINPR_RESTRICT pDstData, UINT32 DstFormat,
                                            UINT32 nDstStep, UINT32 nXDst, UINT32 nYDst,
                                            UINT32 nDstWidth, UINT32 nDstHeight,
                                            const gdiPalette* WINPR_RESTRICT palette)
{
	UINT32 suboffset = 0;

	if (!Stream_CheckAndLogRequiredLength(TAG, s, subcodecByteCount))
		return FALSE;

	while (suboffset < subcodecByteCount)
	{
		if (!Stream_CheckAndLogRequiredLength(TAG, s, 13))
			return FALSE;

		const UINT16 xStart = Stream_Get_UINT16(s);
		const UINT16 yStart = Stream_Get_UINT16(s);
		const UINT16 width = Stream_Get_UINT16(s);
		const UINT16 height = Stream_Get_UINT16(s);
		const UINT32 bitmapDataByteCount = Stream_Get_UINT32(s);
		const UINT8 subcodecId = Stream_Get_UINT8(s);
		suboffset += 13;

		if (!Stream_CheckAndLogRequiredLength(TAG, s, bitmapDataByteCount))
			return FALSE;

		const UINT32 nXDstRel = nXDst + xStart;
		const UINT32 nYDstRel = nYDst + yStart;
		if (1ull * nXDstRel + width > nWidth)
		{
			WLog_ERR(TAG, "nXDstRel %" PRIu16 " + width %" PRIu16 " > nWidth %" PRIu32 "", xStart,
			         width, nWidth);
			return FALSE;
		}
		if (1ull * nYDstRel + height > nHeight)
		{
			WLog_ERR(TAG, "nYDstRel %" PRIu16 " + height %" PRIu16 " > nHeight %" PRIu32 "", yStart,
			         height, nHeight);
			return FALSE;
		}

		if (1ull * xStart + width > nWidth)
		{
			WLog_ERR(TAG, "xStart %" PRIu16 " + width %" PRIu16 " > nWidth %" PRIu32 "", xStart,
			         width, nWidth);
			return FALSE;
		}
		if (1ull * yStart + height > nHeight)
		{
			WLog_ERR(TAG, "yStart %" PRIu16 " + height %" PRIu16 " > nHeight %" PRIu32 "", yStart,
			         height, nHeight);
			return FALSE;
		}

		if (!clear_resize_buffer(clear, width, height))
			return FALSE;

		switch (subcodecId)
		{
			case 0: /* Uncompressed */
			{
				const UINT32 nSrcStep = width * FreeRDPGetBytesPerPixel(PIXEL_FORMAT_BGR24);
				const size_t nSrcSize = 1ull * nSrcStep * height;

				if (bitmapDataByteCount != nSrcSize)
				{
					WLog_ERR(TAG, "bitmapDataByteCount %" PRIu32 " != nSrcSize %" PRIuz "",
					         bitmapDataByteCount, nSrcSize);
					return FALSE;
				}

				if (!convert_color(pDstData, nDstStep, DstFormat, nXDstRel, nYDstRel, width, height,
				                   Stream_Pointer(s), nSrcStep, PIXEL_FORMAT_BGR24, nDstWidth,
				                   nDstHeight, palette))
					return FALSE;

				Stream_Seek(s, bitmapDataByteCount);
			}
			break;

			case 1: /* NSCodec */
				if (!clear_decompress_nscodec(clear->nsc, width, height, s, bitmapDataByteCount,
				                              pDstData, DstFormat, nDstStep, nXDstRel, nYDstRel))
					return FALSE;

				break;

			case 2: /* CLEARCODEC_SUBCODEC_RLEX */
				if (!clear_decompress_subcode_rlex(s, bitmapDataByteCount, width, height, pDstData,
				                                   DstFormat, nDstStep, nXDstRel, nYDstRel,
				                                   nDstWidth, nDstHeight))
					return FALSE;

				break;

			default:
				WLog_ERR(TAG, "Unknown subcodec ID %" PRIu8 "", subcodecId);
				return FALSE;
		}

		suboffset += bitmapDataByteCount;
	}

	return TRUE;
}