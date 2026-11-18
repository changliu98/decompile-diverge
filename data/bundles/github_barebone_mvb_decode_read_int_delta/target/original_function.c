static inline int read_int_delta(const uint8_t* in, uint32_t* out, uint32_t* prev) {
	*out = in[0] & 0x7F;
	if (in[0] < 128) {
		*prev += *out;
		*out = *prev;
		return 1;
	}
	*out = ((in[1] & 0x7FU) << 7) | *out;
	if (in[1] < 128) {
		*prev += *out;
		*out = *prev;
		return 2;
	}
	*out = ((in[2] & 0x7FU) << 14) | *out;
	if (in[2] < 128) {
		*prev += *out;
		*out = *prev;
		return 3;
	}
	*out = ((in[3] & 0x7FU) << 21) | *out;
	if (in[3] < 128) {
		*prev += *out;
		*out = *prev;
		return 4;
	}
	*out = ((in[4] & 0x7FU) << 28) | *out;
	*prev += *out;
	*out = *prev;
	return 5;
}