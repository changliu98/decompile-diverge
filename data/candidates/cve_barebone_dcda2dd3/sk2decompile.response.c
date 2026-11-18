static int read_fru_area(ipmi_intf_t intf, struct fru_info *fi,
                         unsigned char area, unsigned int offset,
                         unsigned int length, unsigned char *data) {
  unsigned int cur_offset = offset;
  unsigned int end_offset;
  unsigned int remaining;
  unsigned char cmd_data[4];
  ipmi_request_t request;
  ipmi_response_t response;
  int rlen;
  if (offset > fi->fru_area_size) {
    lprintf(3, "Read FRU Area offset incorrect: %d > %d", offset,
            fi->fru_area_size);
    return -1;
  }
  end_offset = offset + length;
  if (end_offset > fi->fru_area_size) {
    end_offset = fi->fru_area_size;
    lprintf(5, "Read FRU Area length %d too large, Adjusting to %d",
            offset + length, end_offset - offset);
  }
  memset(&request, 0, sizeof(request));
  request.msg.netfn = 0x0A;
  request.msg.cmd = 0x11;
  request.msg.data = cmd_data;
  request.msg.data_len = sizeof(cmd_data);
  if (fi->fru_read_size == 0) {
    unsigned short max_rsp_size =
        ipmi_intf_get_max_response_data_size(intf) - 1;
    if (max_rsp_size < 2) {
      lprintf(3, "Maximum response size is too small to send a read request");
      return -1;
    }
    if (max_rsp_size - 1 > 255)
      fi->fru_read_size = 0xffffffff;
    else
      fi->fru_read_size = max_rsp_size - 1;
    if (fi->fru_area_flags & 0x01) fi->fru_read_size &= ~0x01;
  }
  do {
    unsigned int cmd_offset;
    if (fi->fru_area_flags & 0x01)
      cmd_offset = cur_offset >> 1;
    else
      cmd_offset = cur_offset;
    cmd_data[0] = area;
    cmd_data[1] = cmd_offset & 0xff;
    cmd_data[2] = cmd_offset >> 8;
    remaining = end_offset - cur_offset;
    if (remaining > fi->fru_read_size)
      cmd_data[3] = fi->fru_read_size;
    else
      cmd_data[3] = remaining;
    response = intf->send(intf, &request);
    if (!response) {
      lprintf(5, "FRU Read failed");
      break;
    }
    if (response->completion_code) {
      if (fru_cc_rq2big(response->completion_code) && fi->fru_read_size > 8) {
        if (fi->fru_read_size > 32)
          fi->fru_read_size -= 8;
        else
          fi->fru_read_size--;
        lprintf(6, "Retrying FRU read with request size %d", fi->fru_read_size);
        continue;
      } else {
        lprintf(5, "FRU Read failed: %s",
                val2str(response->completion_code, &cc_str));
        break;
      }
    }
    if (fi->fru_area_flags & 0x01)
      rlen = response->data[0] << 1;
    else
      rlen = response->data[0];
    memcpy(data, response->data + 1, rlen);
    cur_offset += rlen;
    data += rlen;
    if (rlen == 0 && cur_offset < end_offset) return 0;
  } while (cur_offset < end_offset);
  if (cur_offset < end_offset) return -1;
  return 0;
}