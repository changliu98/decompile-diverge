static inline unsigned int fix_counter(unsigned int counter)
{
  return COUNTER_OVERFLOW - counter;
}