Endian
int __cdecl unicoder_utf32_decode(unsigned int *result, const unsigned __int8 *p, unsigned int endianness)
{
  unsigned int decoded = 0;

  // Validate endianness parameter
  if (endianness != 2 && endianness != 1)
    return ERR_INVALID_ENDIANNESS;
    
  // Validate pointers
  if (!p || !result)
    return ERR_NULL_POINTER;

  // Assemble the 32-bit integer from the 4 bytes
  if (endianness == 2) // Big-Endian
  {
    decoded = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
  }
  else // Little-Endian (endianness == 1)
  {
    decoded = p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
  }

  // Check for invalid Unicode code points (out of range or UTF-16 surrogates)
  if (decoded > UNICODE_MAX_CODE_POINT)
    return ERR_INVALID_CODE_POINT;
    
  if (decoded >= UNICODE_SURROGATE_HIGH_START && decoded <= UNICODE_SURROGATE_LOW_END)
    return ERR_INVALID_CODE_POINT;

  *result = decoded;
  return UTF32_SUCCESS;
}