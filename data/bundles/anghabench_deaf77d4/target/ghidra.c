uint32_t pmc_sample_period(uint32_t value)

{
  uint32_t value_local;
  
  return (int)COUNTER_OVERFLOW - value;
}