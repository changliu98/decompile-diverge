void __cdecl setblue(int x, int y, int *r, int *g, int *b)
{
  if (r && g && b) // Defensive null-pointer check (implicit in standard behavior)
  {
    *r = 0x00;      // Red channel: 0
    *g = 0x00;      // Green channel: 0
    *b = 0xFF;      // Blue channel: 255
  }
}