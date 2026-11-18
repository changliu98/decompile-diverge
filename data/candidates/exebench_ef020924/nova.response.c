static inline void swapfloat(void *data)
{
	unsigned int *buf = data;

	*buf = ((*buf & 0x00FF00FF) << 8) | ((*buf & 0xFF00FF00) >> 8);
	*buf = ((*buf & 0x0F0F0F0F) << 4) | ((*buf & 0xF0F0F0F0) >> 4);
	*buf = ((*buf & 0x33333333) << 2) | ((*buf & 0xCCCCCCCC) >> 2);
	*buf = ((*buf & 0x55555555) << 1) | ((*buf & 0xAAAAAAAA) >> 1);
}