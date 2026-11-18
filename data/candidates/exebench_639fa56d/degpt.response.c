// Advances the m2pos value by 1, wrapping around at 0x25 (37)
void advance_m2pos(int *position)
{
  // Increment m2pos and apply modulo 0x25 to keep it within bounds [0, 36]
  *position = (*position + 1) % 0x25;
}