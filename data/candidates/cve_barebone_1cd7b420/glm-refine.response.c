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

  if (rec_counter > 10)
    return 320043;

  *parsed_len = 0;
  *name_len = 0;
  p = start;

  while (1)
  {
    if (!*p)
    {
      ++p;
      ++*parsed_len;
      return 0;
    }

    if ((*p & 0xC0) == 0xC0)
      break;

    label_len = *p;
    if (&pkt[*p] > max)
      return 320043;

    p += label_len + 1;
    *parsed_len += label_len + 1;

    if (*p)
      ++label_len;

    *name_len += label_len;

    if (p >= max)
      return 320041;
  }

  ptr_len = 0;
  pj_memcpy(&offset, p, 2uLL);
  offset ^= foldCase(0xC000u);
  offset = foldCase(offset);

  if (offset >= max - pkt)
    return 320043;

  status = get_name_len(rec_counter + 1, pkt, &pkt[offset], max, &dummy, &ptr_len);
  if (status)
    return status;

  *parsed_len += 2;
  *name_len += ptr_len;

  return 0;
}