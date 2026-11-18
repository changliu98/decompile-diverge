static inline unsigned int pmc_sample_period(unsigned int last_sample) {
  unsigned int sample_period;
  sample_period = pmc_current_time - last_sample;
  return sample_period;
}