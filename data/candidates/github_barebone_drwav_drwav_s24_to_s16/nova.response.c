static void drwav_s24_to_s16(short *output, const unsigned char *input, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++) {
		int v = (int)(input[3 * i + 0] << 0) |
			(input[3 * i + 1] << 8) |
			(input[3 * i + 2] << 16);
		int t = v >> 8;
		output[i] = (short)(t);
	}
}