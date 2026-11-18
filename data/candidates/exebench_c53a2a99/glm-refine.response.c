void __cdecl unhide(char *text)
{
  // The key array is initialized with the values {3, 16, 2}.
  // This is derived from the little-endian representation of 0x100000003LL and iOile[2] = 2.
  const unsigned char key[3] = { 3, 16, 2 };
  int key_idx = 0;

  for (int i = 0; text[i]; ++i)
  {
    // Subtract the current key byte from the text character
    text[i] -= key[key_idx++];
    
    // Wrap around the key index after 3 iterations
    if (key_idx == 3)
      key_idx = 0;
  }
}