static inline unsigned int calc_rms(unsigned int rms, unsigned int energy)
{
  return (rms * energy) >> 10;
}