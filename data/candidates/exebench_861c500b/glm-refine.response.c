char *__cdecl fix(char *dst, char *src)
{
  size_t src_idx = 0;
  size_t dst_idx = 0;

  // Iterate through the source string until the null terminator
  while (src[src_idx])
  {
    if (src[src_idx] == '\b') // ASCII 8 is the backspace character
    {
      // Simulate a backspace by decrementing the destination index,
      // ensuring it doesn't go below zero.
      if (dst_idx > 0)
        --dst_idx;
    }
    else
    {
      // Copy the character to the destination and advance the index
      dst[dst_idx++] = src[src_idx];
    }
    ++src_idx;
  }
  
  // Null-terminate the destination string
  dst[dst_idx] = '\0';
  
  return dst;
}