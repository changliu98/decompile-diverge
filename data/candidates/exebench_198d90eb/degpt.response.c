void advance_kpos(int *position)
{
  // Increment kpos[0] modulo 0x29 (41)
  *position = (*position + 1) % 0x29;
  // Increment kpos[1] modulo 0x1f (31)
  position[1] = (position[1] + 1) % 0x1f;
  // Increment kpos[2] modulo 0x1d (29)
  position[2] = (position[2] + 1) % 0x1d;
  // Increment kpos[3] modulo 0x1a (26)
  position[3] = (position[3] + 1) % 0x1a;
  // Increment kpos[4] modulo 0x17 (23)
  position[4] = (position[4] + 1) % 0x17;
}