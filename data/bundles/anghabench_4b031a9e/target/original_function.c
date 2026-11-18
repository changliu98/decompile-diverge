int
valid_bo_pre_v2 (long value)
{
  /* Certain encodings have bits that are required to be zero.
     These are (z must be zero, y may be anything):
	 0000y
	 0001y
	 001zy
	 0100y
	 0101y
	 011zy
	 1z00y
	 1z01y
	 1z1zz
  */
  if ((value & 0x14) == 0)
    return 1;
  else if ((value & 0x14) == 0x4)
    return (value & 0x2) == 0;
  else if ((value & 0x14) == 0x10)
    return (value & 0x8) == 0;
  else
    return value == 0x14;
}