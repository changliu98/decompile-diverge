int __cdecl minor_to_index(int minor)
{
  return minor >> PART_BITS;
}