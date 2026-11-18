char *__cdecl scnline(int key, char *p, int c)
{
  int scnwidth = 7; // The loop pre-decrements from 8 to 1, running exactly 7 times.

  while (scnwidth--)
  {
    key <<= 1; // Multiply key by 2
    
    // Check if the most significant bit (MSB) of the byte is set
    *p++ = (key & 0x80) ? (char)c : ' '; // 32 is the ASCII code for space ' '
  }
  
  return p;
}