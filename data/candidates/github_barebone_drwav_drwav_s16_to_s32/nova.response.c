void drwav_s16_to_s32(u32 *dst, short *src, size_t n)
{
	size_t i;

	if (!dst ||!src)
		return;

	for (i = 0; i < n; i++) {
		*dst++ = (u32)*src++ << 16;
	}
}