__attribute__((used)) static inline u64 pmc_sample_period(u64 new, u64 old)
{
	return COUNTER_OVERFLOW - new + old;
}