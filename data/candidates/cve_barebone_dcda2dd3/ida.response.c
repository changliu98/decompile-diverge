int __cdecl read_fru_area(
        ipmi_intf *intf,
        fru_info *fru,
        uint8_t id,
        uint32_t offset,
        uint32_t length,
        uint8_t *frubuf)
{
  uint8_t v6; // cl
  const char *v7; // rax
  uint32_t v9; // [rsp+8h] [rbp-68h]
  uint32_t v10; // [rsp+Ch] [rbp-64h]
  uint16_t max_rs_size; // [rsp+12h] [rbp-5Eh]
  uint8_t msg_data[4]; // [rsp+14h] [rbp-5Ch] BYREF
  ipmi_rq req; // [rsp+18h] [rbp-58h] BYREF
  ipmi_rs *rsp_0; // [rsp+28h] [rbp-48h]
  uint32_t finish; // [rsp+34h] [rbp-3Ch]
  uint32_t tmp; // [rsp+38h] [rbp-38h]
  uint32_t off; // [rsp+3Ch] [rbp-34h]
  uint8_t *frubufa; // [rsp+40h] [rbp-30h]
  uint32_t lengtha; // [rsp+4Ch] [rbp-24h]
  uint32_t offseta; // [rsp+50h] [rbp-20h]
  uint8_t ida; // [rsp+57h] [rbp-19h]
  fru_info *frua; // [rsp+58h] [rbp-18h]
  ipmi_intf *intfa; // [rsp+60h] [rbp-10h]

  intfa = intf;
  frua = fru;
  ida = id;
  offseta = offset;
  lengtha = length;
  frubufa = frubuf;
  off = offset;
  if ( offset > fru->size )
  {
    lprintf(3, "Read FRU Area offset incorrect: %d > %d", offseta, frua->size);
    return -1;
  }
  finish = lengtha + offseta;
  if ( lengtha + offseta > frua->size )
  {
    finish = frua->size;
    lprintf(5, "Read FRU Area length %d too large, Adjusting to %d", lengtha + offseta, finish - offseta);
  }
  memset(&req, 0, sizeof(req));
  *(_BYTE *)&req.msg = *(_BYTE *)&req.msg & 0xC0 | 0xA;
  req.msg.cmd = 17;
  req.msg.data = msg_data;
  req.msg.data_len = 4;
  if ( !frua->max_read_size )
  {
    max_rs_size = ipmi_intf_get_max_response_data_size(intfa) - 1;
    if ( max_rs_size > 1u )
    {
      if ( max_rs_size - 1 <= 255 )
        frua->max_read_size = max_rs_size - 1;
      else
        frua->max_read_size = -1;
      if ( (*((_BYTE *)frua + 2) & 1) != 0 )
        frua->max_read_size &= ~1u;
      goto LABEL_13;
    }
    lprintf(3, "Maximum response size is too small to send a read request");
    return -1;
  }
  while ( 1 )
  {
LABEL_13:
    if ( (*((_BYTE *)frua + 2) & 1) != 0 )
      v10 = off >> 1;
    else
      LOWORD(v10) = off;
    msg_data[0] = ida;
    *(_WORD *)&msg_data[1] = v10;
    tmp = finish - off;
    if ( finish - off <= frua->max_read_size )
      msg_data[3] = tmp;
    else
      msg_data[3] = frua->max_read_size;
    rsp_0 = (ipmi_rs *)intfa->sendrecv(intfa, &req);
    if ( !rsp_0 )
    {
      lprintf(5, "FRU Read failed");
      goto LABEL_36;
    }
    if ( !rsp_0->ccode )
    {
      if ( (*((_BYTE *)frua + 2) & 1) != 0 )
        v9 = 2 * rsp_0->data[0];
      else
        v9 = rsp_0->data[0];
      tmp = v9;
      memcpy(frubufa, &rsp_0->data[1], v9);
      off += tmp;
      frubufa += tmp;
      if ( !tmp && off < finish )
        return 0;
      goto LABEL_35;
    }
    if ( !fru_cc_rq2big(rsp_0->ccode) || frua->max_read_size <= 8u )
      break;
    if ( frua->max_read_size <= 0x20u )
      v6 = frua->max_read_size - 1;
    else
      v6 = frua->max_read_size - 8;
    frua->max_read_size = v6;
    lprintf(6, "Retrying FRU read with request size %d", frua->max_read_size);
LABEL_35:
    if ( off >= finish )
      goto LABEL_36;
  }
  v7 = val2str(rsp_0->ccode, &completion_code_vals);
  lprintf(5, "FRU Read failed: %s", v7);
LABEL_36:
  if ( off >= finish )
    return 0;
  else
    return -1;
}