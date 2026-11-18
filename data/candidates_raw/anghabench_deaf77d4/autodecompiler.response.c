__attribute__((used)) static inline u64 counter_diff(u64 new, u64 old)
{
	return COUNTER_OVERFLOW - new + old;
}