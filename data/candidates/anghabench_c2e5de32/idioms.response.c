static inline unsigned int ff_rescale_rms(unsigned int rms, unsigned int energy)
{
  return (rms * energy) >> 10;
}