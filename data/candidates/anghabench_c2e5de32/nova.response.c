static inline unsigned int ff_rescale_rms(unsigned int width,
					     unsigned int depth)
{
	return (width * depth) >> 10;
}