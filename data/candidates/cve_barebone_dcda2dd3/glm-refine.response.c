int __cdecl read_fru_area(
        ipmi_intf *intf,
        fru_info *fru,
        uint8_t id,
        uint32_t offset,
        uint32_t length,
        uint8_t *frubuf)
{
  uint16_t max_rs_size;
  uint8_t msg_data[4];
  ipmi_rq req;
  ipmi_rs *rsp;
  uint32_t finish;
  uint32_t tmp;
  uint32_t off;
  uint8_t *frubufa;
  uint8_t new_max_read_size;

  off = offset;
  frubufa = frubuf;

  if (offset > fru->size)
  {
    lprintf(3, "Read FRU Area offset incorrect: %d > %d", offset, fru->size);
    return -1;
  }

  finish = length + offset;
  if (finish > fru->size)
  {
    finish = fru->size;
    lprintf(5, "Read FRU Area length %d too large, Adjusting to %d", length + offset, finish - offset);
  }

  memset(&req, 0, sizeof(req));
  req.msg.netfn = (req.msg.netfn & 0xC0) | 0xA; // Preserve high bits, set netfn to 0x0A (Storage)
  req.msg.cmd = 17;                             // 0x11: Get FRU Read Data
  req.msg.data = msg_data;
  req.msg.data_len = 4;

  if (!fru->max_read_size)
  {
    max_rs_size = ipmi_intf_get_max_response_data_size(intf) - 1;
    if (max_rs_size > 1)
    {
      if (max_rs_size - 1 <= 255)
        fru->max_read_size = max_rs_size - 1;
      else
        fru->max_read_size = -1; // 0xFF

      if ((fru->flags & 1) != 0)
        fru->max_read_size &= ~1u; // Align to even size for 16-bit access

      goto LABEL_13;
    }
    lprintf(3, "Maximum response size is too small to send a read request");
    return -1;
  }

  while (1)
  {
LABEL_13:
    if ((fru->flags & 1) != 0)
      *(_WORD *)&msg_data[1] = off >> 1; // 16-bit word offset
    else
      *(_WORD *)&msg_data[1] = off;      // Byte offset

    msg_data[0] = id;

    tmp = finish - off;
    if (tmp <= fru->max_read_size)
      msg_data[3] = tmp;
    else
      msg_data[3] = fru->max_read_size;

    rsp = (ipmi_rs *)intf->sendrecv(intf, &req);
    if (!rsp)
    {
      lprintf(5, "FRU Read failed");
      goto LABEL_36;
    }

    if (!rsp->ccode)
    {
      if ((fru->flags & 1) != 0)
        tmp = 2 * rsp->data[0]; // 16-bit word count to byte count
      else
        tmp = rsp->data[0];

      memcpy(frubufa, &rsp->data[1], tmp);
      off += tmp;
      frubufa += tmp;

      if (!tmp && off < finish)
        return 0;

      goto LABEL_35;
    }

    if (!fru_cc_rq2big(rsp->ccode) || fru->max_read_size <= 8)
      break;

    if (fru->max_read_size <= 0x20)
      new_max_read_size = fru->max_read_size - 1;
    else
      new_max_read_size = fru->max_read_size - 8;

    fru->max_read_size = new_max_read_size;
    lprintf(6, "Retrying FRU read with request size %d", fru->max_read_size);

LABEL_35:
    if (off >= finish)
      goto LABEL_36;
  }

  lprintf(5, "FRU Read failed: %s", val2str(rsp->ccode, &completion_code_vals));

LABEL_36:
  if (off >= finish)
    return 0;
  else
    return -1;
}