static inline unsigned int pmc_sample_period(unsigned int counter)
{
  return COUNTER_OVERFLOW - counter;
}