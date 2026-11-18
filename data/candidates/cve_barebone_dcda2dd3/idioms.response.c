int read_fru_area(struct ipmi_intf *intf, struct fru_info *fru, unsigned char id, unsigned int offset, unsigned int length, unsigned char *frubuf)
{
  struct ipmi_rq rq;
  struct ipmi_rs *rs;
  struct ipmi_msg *msg;
  unsigned char *data;
  unsigned int data_len;
  unsigned int read_len;
  unsigned int read_id;
  unsigned int read_offset;
  unsigned int read_size;
  unsigned int max_rs_size;
  int i;
  int ccode;
  int retry;
  int retry_count = 0;
  intf = intf;
  fru = fru;
  id = id;
  offset = offset;
  length = length;
  frubuf = frubuf;
  read_offset = offset;
  if (read_offset > fru->size) {
    log_print(3, "Read FRU Area offset incorrect: %d > %d", read_offset, fru->size);
    return -1;
  }
  read_size = read_offset + length;
  if (read_size > fru->size) {
    read_size = fru->size;
    log_print(5, "Read FRU Area length %d too large, Adjusting to %d", read_size - read_offset, read_size);
  }
  ipmi_init_rq(&rq, 0, sizeof(struct ipmi_msg));
  msg = &rq.msg;
  msg->netfn = 0x0a;
  msg->cmd = 0x11;
  data = msg->data;
  data_len = msg->data_len = sizeof(read_id) + sizeof(read_offset) + sizeof(read_len);
  if (fru->max_read_size == 0) {
    max_rs_size = get_max_rs_size(intf) - 1;
    if (max_rs_size < sizeof(struct ipmi_rs_base)) {
      log_print(3, "Maximum response size is too small to send a read request");
      return -1;
    }
    if (max_rs_size - sizeof(struct ipmi_rs_base) > 255)
      fru->max_read_size = -1;
    else
      fru->max_read_size = max_rs_size - sizeof(struct ipmi_rs_base);
    if (fru->type & 0x1)
      fru->max_read_size &= ~0x1;
  }
  for (;;) {
    if (fru->type & 0x1)
      read_id = (read_offset & ~0x1) / 2;
    else
      read_id = (read_offset & ~0xff) / 256;
    data[0] = id;
    data[1] = read_id & 0xff;
    data[2] = read_id >> 8;
    if (read_size - read_offset > fru->max_read_size)
      data[3] = fru->max_read_size;
    else
      data[3] = read_size - read_offset;
    rs = intf->sendrecv(intf, &rq);
    if (rs == ((void *)0)) {
      log_print(5, "FRU Read failed");
      break;
    }
    if (rs->ccode == 0) {
      if (fru->type & 0x1)
        read_len = (rs->data[0] * 2);
      else
        read_len = (rs->data[0] * 256);
      read_len = read_len + sizeof(struct ipmi_rs_base);
      memcpy(frubuf, &rs->data[1], read_len);
      read_offset += read_len;
      frubuf += read_len;
      if (read_len == 0 && read_offset < read_size)
        return 0;
    } else {
      if (is_retryable(rs->ccode) && fru->max_read_size > sizeof(struct ipmi_rs_base)) {
        if (fru->max_read_size > sizeof(struct ipmi_rs))
          fru->max_read_size = fru->max_read_size - sizeof(struct ipmi_rs_base);
        else
          fru->max_read_size = fru->max_read_size - sizeof(struct ipmi_rs);
        log_print(6, "Retrying FRU read with request size %d", fru->max_read_size);
        continue;
      }
      log_print(5, "FRU Read failed: %s", get_completion_code_str(rs->ccode, completion_code_vals));
      break;
    }
    if (read_offset >= read_size)
      break;
  }
  if (read_offset < read_size)
    return -1;
  return 0;
}