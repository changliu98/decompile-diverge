void __cdecl func0(char *str, int encode)
{
  char block[4];      // 3 chars + null terminator
  int len = strlen(str);
  int chunks = (len + 2) / 3; // Equivalent to ceil(len / 3.0)

  for (int i = 0; i < chunks; ++i)
  {
    // Determine how many characters are in the current chunk (handles remainder)
    int chunk_size = (3 * i + 3 > len) ? (len - 3 * i) : 3;

    // Extract the 3-byte chunk and null-terminate it
    strncpy(block, &str[3 * i], chunk_size);
    block[chunk_size] = 0;

    // Only rotate if the chunk is exactly 3 characters
    if (chunk_size == 3)
    {
      if (encode)
      {
        // Encode: Rotate left (c -> a, a -> b, b -> c)
        char temp = block[2];
        block[2] = block[1];
        block[1] = block[0];
        block[0] = temp;
      }
      else
      {
        // Decode: Rotate right (b -> a, c -> b, a -> c)
        char temp = block[0];
        block[0] = block[1];
        block[1] = block[2];
        block[2] = temp;
      }
    }

    // Write the transformed chunk back to the string
    strncpy(&str[3 * i], block, chunk_size);
  }
}