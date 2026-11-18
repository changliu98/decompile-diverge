void __cdecl word2string(unsigned int value, char *buffer)
{
  char *p = buffer;
  
  if (value)
  {
    for (int c = 0; c < 5; ++c)
    {
      // Skip leading zeros (or rather, skip if the current digit position would be at the start of the buffer)
      if (&p[value / word2string__smth[c]] != buffer)
      {
        *p++ = (value / word2string__smth[c]) + '0';
        value %= word2string__smth[c];
      }
    }
    // Write a 2-byte space character padding (0x20, 0x20)
    *(_WORD *)p = 0x2020; 
  }
  else
  {
    // Write "0  " (0x30, 0x20, 0x20, 0x00) for the zero case
    *(_DWORD *)buffer = 0x00202030;
  }
}