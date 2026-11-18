define DNS_POINTER_MASK 0xC0

pj_status_t __cdecl get_name_len(
        int rec_counter,
        const pj_uint8_t *pkt,
        const pj_uint8_t *start,
        const pj_uint8_t *max,
        int *parsed_len,
        int *name_len)
{
  unsigned int label_len;
  pj_uint16_t offset;
  int dummy;
  int ptr_len;
  pj_status_t status;
  const pj_uint8_t *p;

  // Recursion depth check to prevent infinite loops
  if (rec_counter > MAX_RECURSION_DEPTH)
    return PJ_STATUS_DNS_INVALID_NAME;

  // Bounds check
  if (start >= max)
    return PJ_STATUS_DNS_INVALID_NAME;

  *parsed_len = 0;
  *name_len = 0;
  p = start;

  while (1)
  {
    // Null byte indicates the end of the DNS name
    if (*p == 0)
    {
      ++p;
      ++*parsed_len;
      return 0;
    }

    // Check if the current byte is a DNS compression pointer (0xC0)
    if ((*p & DNS_POINTER_MASK) == DNS_POINTER_MASK)
      break;

    // Regular label
    label_len = *p;
    
    // Bounds check: ensure the label and the next length byte don't exceed the buffer
    if (&p[label_len + 2] > max)
      return PJ_STATUS_DNS_INVALID_NAME;

    // Advance pointer and update parsed length
    p += label_len + 1;
    *parsed_len += label_len + 1;

    // If there is another label following, account for the dot separator
    if (*p != 0)
      ++label_len;

    *name_len += label_len;
  }

  // Handle DNS compression pointer
  ptr_len = 0;
  pj_memcpy(&offset, p, 2uLL);
  
  // Extract the 14-bit offset from the 16-bit pointer
  offset ^= foldCase(0xC000u);
  offset = foldCase(offset);

  // Bounds check for the pointer offset
  if (offset >= (pj_uint16_t)(max - pkt))
    return PJ_STATUS_DNS_INVALID_NAME;

  // Recursively resolve the rest of the name from the pointer offset
  status = get_name_len(rec_counter + 1, pkt, &pkt[offset], max, &dummy, &ptr_len);
  if (status)
    return status;

  // Update lengths: 2 bytes for the pointer itself, plus the length from the resolved name
  *parsed_len += 2;
  *name_len += ptr_len;

  return 0;
}