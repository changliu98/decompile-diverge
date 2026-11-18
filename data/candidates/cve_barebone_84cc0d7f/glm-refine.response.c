void __cdecl faad_resetbits(bitfile *ld, int bits)
{
  // Calculate the number of whole 32-bit words to skip
  int words = bits >> 5;
  
  // Calculate the remaining bits within the current 32-bit word
  int remainder = bits & 0x1F;
  
  // Update the remaining bytes in the buffer
  ld->bytes_left = ld->buffer_size - 4 * words;

  uint32_t tmp;
  if (ld->bytes_left < 4)
  {
    // Read a partial 32-bit word if fewer than 4 bytes are left
    tmp = getdword_n(&ld->start[words], ld->bytes_left);
    ld->bytes_left = 0;
  }
  else
  {
    // Read a full 32-bit word and decrement the remaining byte count
    tmp = getdword(&ld->start[words]);
    ld->bytes_left -= 4;
  }
  ld->bufa = tmp;

  uint32_t tmpa;
  if (ld->bytes_left < 4)
  {
    // Read a partial 32-bit word for the second buffer if fewer than 4 bytes are left
    tmpa = getdword_n(&ld->start[words + 1], ld->bytes_left);
    ld->bytes_left = 0;
  }
  else
  {
    // Read a full 32-bit word for the second buffer and decrement the remaining byte count
    tmpa = getdword(&ld->start[words + 1]);
    ld->bytes_left -= 4;
  }
  ld->bufb = tmpa;

  // Set the number of valid bits left in the primary buffer register
  ld->bits_left = 32 - remainder;
  
  // Update the tail pointer to point to the next unbuffered word
  ld->tail = &ld->start[words + 2];
  
  // Clear any previous errors
  ld->error = 0;
}