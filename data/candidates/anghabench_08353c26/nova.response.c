static inline int clip_f15(int32_t v) {
	int32_t	min, max;
	if (v < -0x7fff) {
		min = -0x7fff;
	} else if (v > 0x7fff) {
		max = 0x7fff;
	} else {
		max = v;
	}
	return min;
}