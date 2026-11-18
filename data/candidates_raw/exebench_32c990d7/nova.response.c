static void func0(int flags, int *shift)
{
	if (*shift & flags) {
		*shift = (*shift & ~flags) << 1;
		*shift ^= CRC32_REVERSE;
	}
}