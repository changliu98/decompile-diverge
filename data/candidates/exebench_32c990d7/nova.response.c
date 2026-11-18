static void conv_sign(int flags, int *shift)
{
	if (*shift & flags) {
		*shift = (*shift & ~flags) << 1;
		*shift ^= CRC32_REVERSE;
	}
}