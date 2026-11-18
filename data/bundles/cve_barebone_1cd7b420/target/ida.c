pj_status_t __cdecl get_name_len(
        int rec_counter,
        const pj_uint8_t *pkt,
        const pj_uint8_t *start,
        const pj_uint8_t *max,
        int *parsed_len,
        int *name_len)
{
  unsigned int label_len; // [rsp+4h] [rbp-4Ch]
  pj_uint16_t offset; // [rsp+Ah] [rbp-46h] BYREF
  int dummy; // [rsp+Ch] [rbp-44h] BYREF
  int ptr_len; // [rsp+10h] [rbp-40h] BYREF
  pj_status_t status; // [rsp+14h] [rbp-3Ch]
  const pj_uint8_t *p; // [rsp+18h] [rbp-38h]
  int *name_lena; // [rsp+20h] [rbp-30h]
  int *parsed_lena; // [rsp+28h] [rbp-28h]
  const pj_uint8_t *maxa; // [rsp+30h] [rbp-20h]
  const pj_uint8_t *starta; // [rsp+38h] [rbp-18h]
  const pj_uint8_t *pkta; // [rsp+40h] [rbp-10h]
  int rec_countera; // [rsp+48h] [rbp-8h]

  rec_countera = rec_counter;
  pkta = pkt;
  starta = start;
  maxa = max;
  parsed_lena = parsed_len;
  name_lena = name_len;
  if ( rec_counter > 10 )
    return 320043;
  *parsed_lena = 0;
  *name_lena = 0;
  p = starta;
  while ( 1 )
  {
    if ( !*p )
    {
      ++p;
      ++*parsed_lena;
      return 0;
    }
    if ( (*p & 0xC0) == 192 )
      break;
    label_len = *p;
    if ( &pkta[*p] > maxa )
      return 320043;
    p += label_len + 1;
    *parsed_lena += label_len + 1;
    if ( *p )
      ++label_len;
    *name_lena += label_len;
    if ( p >= maxa )
      return 320041;
  }
  ptr_len = 0;
  pj_memcpy(&offset, p, 2uLL);
  offset ^= foldCase(0xC000u);
  offset = foldCase(offset);
  if ( offset >= maxa - pkta )
    return 320043;
  status = get_name_len(rec_countera + 1, pkta, &pkta[offset], maxa, &dummy, &ptr_len);
  if ( status )
    return status;
  *parsed_lena += 2;
  *name_lena += ptr_len;
  return 0;
}