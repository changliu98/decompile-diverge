int minor_to_index(int minor)

{
  int minor_local;
  
  return minor >> ((byte)PART_BITS & 0x1f);
}