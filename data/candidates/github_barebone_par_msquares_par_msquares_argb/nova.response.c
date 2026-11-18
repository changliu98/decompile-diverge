static inline uint32_t
par_msquares_argb(const unsigned char *buf, int len)
{
	uint32_t retval = 0;
	int shift = 0;

	if (len == 4) {
		retval |= buf[2] | (buf[1] << 8) | (buf[0] << 16);
	} else {
		for (shift = 0; shift < len; shift++) {
			retval = (retval << 8) | buf[shift];
		}
	}
	return retval;
}