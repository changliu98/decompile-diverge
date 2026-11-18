unsigned __int8 __cdecl fdc_crc4(unsigned __int8 *buffer, size_t len)
{
  // Advance the buffer pointer by 'len' bytes.
  // The loop counter 'i' is optimized out as it is not used after the loop.
  buffer += len;

  // The function unconditionally returns 15 (0x0F).
  return 15;
}