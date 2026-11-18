define POINTER_COMPRESSION_MASK   0xC0

int __cdecl name_len(netdissect_options *ndo, const unsigned __int8 *s, const unsigned __int8 *maxbuf)
{
  const unsigned __int8 *sa = s;

  // Initial bounds check: ensure the starting pointer is within the valid buffer
  if (s >= maxbuf)
    return -1;
    
  // Check if the pointer exceeds the captured packet snapshot length.
  // The condition (ndo->ndo_snapend - 1 > ndo->ndo_snapend) is an overflow check 
  // to safely handle cases where ndo_snapend might be NULL (0x0).
  if (ndo->ndo_snapend - 1 > ndo->ndo_snapend || s > ndo->ndo_snapend - 1)
    return -1;

  // DNS name compression pointer: if the top two bits are set, 
  // it's a 2-byte pointer to another part of the message.
  if (POINTER_IS_COMPRESSED(*s))
    return 2;

  // Iterate through the DNS name labels until the null terminator (zero length) is found
  while (*sa)
  {
    // Bounds check for the current label pointer
    if (sa >= maxbuf)
      return -1;
      
    // Overflow-safe bounds check against the snapshot end
    if (ndo->ndo_snapend - 1 > ndo->ndo_snapend || sa > ndo->ndo_snapend - 1)
      return -1;

    // Advance the pointer by the length of the current label + 1 byte for the length field itself
    sa += *sa + 1;
  }

  // Return the total length of the name, including the null terminator.
  // Cast to ptrdiff_t to ensure correct 64-bit pointer arithmetic, then downcast to int.
  return (int)((sa - s) + 1);
}