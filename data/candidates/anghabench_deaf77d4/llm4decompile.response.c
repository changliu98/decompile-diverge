uint32_t pmc_sample_period(uint32_t value)
{
 return (uint32_t)COUNTER_OVERFLOW - value;
}