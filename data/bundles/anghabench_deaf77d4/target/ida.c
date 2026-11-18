uint32_t __cdecl pmc_sample_period(uint32_t value)
{
  return COUNTER_OVERFLOW - value;
}