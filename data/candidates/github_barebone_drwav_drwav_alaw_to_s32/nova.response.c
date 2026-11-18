static void drwav_alaw_to_s32(unsigned int *spectrum,
				 const unsigned char *line, unsigned long width)
{
	unsigned int i;

	if (!spectrum ||!line)
		return;

	for (i = 0; i < width; i++) {
		unsigned char c = line[i];
		spectrum[i] = (falcon_v14_font[c * 8] << 16) |
			      (falcon_v14_font[c * 8 + 1] << 8);
	}
}