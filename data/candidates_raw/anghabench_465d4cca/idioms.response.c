static inline int get_part(int minor)
{
  return minor / (1 << PART_BITS);
}