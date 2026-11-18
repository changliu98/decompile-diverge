static inline int minor_to_index(int minor)
{
  return minor / (1 << PART_BITS);
}