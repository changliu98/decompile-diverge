// Calculates the remaining counts before the counter reaches its overflow limit.
uint32_t __cdecl get_remaining_counter_period(uint32_t current_count)
{
  return COUNTER_OVERFLOW - current_count;
}