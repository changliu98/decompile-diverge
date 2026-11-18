static BOOL resize_vbar_entry(CLEAR_CONTEXT* WINPR_RESTRICT clear,
                              CLEAR_VBAR_ENTRY* WINPR_RESTRICT vBarEntry)
{
	if (vBarEntry->count > vBarEntry->size)
	{
		const UINT32 bpp = FreeRDPGetBytesPerPixel(clear->format);
		const UINT32 oldPos = vBarEntry->size * bpp;
		const UINT32 diffSize = (vBarEntry->count - vBarEntry->size) * bpp;

		vBarEntry->size = vBarEntry->count;
		BYTE* tmp =
		    (BYTE*)winpr_aligned_recalloc(vBarEntry->pixels, vBarEntry->count, 1ull * bpp, 32);

		if (!tmp)
		{
			WLog_ERR(TAG, "vBarEntry->pixels winpr_aligned_recalloc %" PRIu32 " failed",
			         vBarEntry->count * bpp);
			return FALSE;
		}

		memset(&tmp[oldPos], 0, diffSize);
		vBarEntry->pixels = tmp;
	}

	if (!vBarEntry->pixels && vBarEntry->size)
	{
		WLog_ERR(TAG, "vBarEntry->pixels is nullptr but vBarEntry->size is %" PRIu32 "",
		         vBarEntry->size);
		return FALSE;
	}

	return TRUE;
}