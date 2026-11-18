static void func0(float *output, unsigned char *input, size_t len)
{
	size_t i;

	if (!output ||!input)
		return;

	for (i = 0; i < len; i++) {
		unsigned char v = input[i];

		output[i] = ((float)v - 128.0f) / 127.0f;
	}
}