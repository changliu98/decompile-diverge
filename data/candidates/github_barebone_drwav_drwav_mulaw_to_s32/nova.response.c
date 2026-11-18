static void drwav_mulaw_to_s32(void *font, const void *font_data, size_t font_size)
{
	const uint8_t *data = font_data;
	unsigned i;

	if (!font ||!font_data)
		return;

	for (i = 0; i < font_size; i++) {
		uint16_t glyph = data[i];
		uint16_t *glyph_data = ((uint16_t *)font) + (glyph * 32);

		font = (uint16_t *)font + 32;
		memcpy(font, glyph_data, 32 * sizeof(uint16_t));
		font = (uint16_t *)font + 32;
	}
}