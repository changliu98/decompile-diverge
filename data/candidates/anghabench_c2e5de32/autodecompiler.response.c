unsigned int ff_rescale_rms(unsigned int x, unsigned int y)
{
 return ((unsigned long)x * (unsigned long)y) >> 10;
}