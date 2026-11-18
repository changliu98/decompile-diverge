char *__cdecl emit_literal(char *op, const char *literal, int len, bool allow_fast_path)
{
  int n = len - 1;
  char *payload = op + 1;

  if (n >= 60)
  {
    int count = 0;
    while (n > 0)
    {
      payload[count] = (char)n;
      n >>= 8;
      ++count;
    }
    
    // Asserts ensuring the variable-length integer fits in 1 to 4 bytes
    assert(count >= 1);
    assert(count <= 4);
    
    *op = 4 * (count + 59);
  }
  else
  {
    *op = 4 * n;
  }

  if (!allow_fast_path || len > 16)
  {
    memcpy(payload, literal, len);
  }
  else
  {
    // Fast path for literals up to 16 bytes
    unaligned_copy64(literal, payload);
    unaligned_copy64(literal + 8, op + 9);
  }

  return &payload[len];
}