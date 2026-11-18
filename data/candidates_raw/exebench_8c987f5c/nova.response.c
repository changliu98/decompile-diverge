static char *
func0(int8_t scale, int16_t exponent, int32_t *mantissa)
{
	char *units = "BKMGTPEZY";
	int unit = 4;

	if (scale < 0) {
		if (exponent < 256) {
			units = "munp";
			unit = 1;
		} else if (exponent < 65536) {
			units = "kMtPEZY";
			unit = 2;
		} else {
			units = "numic";
			unit = 4;
		}
	} else if (scale >= -99) {
		if (exponent < 128 && exponent >= 0) {
			units = "munp";
			unit = 1;
		} else if (exponent < -99 && exponent >= -32768) {
			units = "kMtPEZY";
			unit = 2;
		}
	}
	if (mantissa)
		*mantissa = unit;
	return (units);
}