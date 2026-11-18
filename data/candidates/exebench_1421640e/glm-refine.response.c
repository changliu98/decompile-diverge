void __cdecl encode_vector(char *c, int x, int y)
{
  // Encode the Y coordinate into two characters
  // Extract the upper 5 bits of Y and map to ASCII 32-63 (' ' to '?')
  c[0] = (y >> 5) + 32; 
  
  // Extract the lower 5 bits of Y and map to ASCII 96-127 ('`' to DEL)
  c[1] = (y & 0x1F) + 96; 

  // Encode the X coordinate into two characters
  // Extract the upper 5 bits of X and map to ASCII 32-63 (' ' to '?')
  c[2] = (x >> 5) + 32; 
  
  // Extract the lower 5 bits of X and map to ASCII 64-95 ('@' to '_')
  c[3] = (x & 0x1F) + 64; 

  // Null-terminate the resulting 4-character string
  c[4] = 0;
}