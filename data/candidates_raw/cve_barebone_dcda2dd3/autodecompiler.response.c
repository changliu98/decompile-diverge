static int
ipmi_fru_read_area(struct ipmi_interface * intf, struct fru_area * area,
   unsigned char id, unsigned int offset, unsigned int length,
   unsigned char * buf)
{
 struct ipmi_rq req;
 unsigned char msg_data[4];
 unsigned char * rsp;
 unsigned int rsplen;
 unsigned int max_rs_size;
 unsigned int end_offset;
 unsigned int cur_offset;
 unsigned int bytes_left;
 unsigned int bytes_to_read;
 int rv;

 cur_offset = offset;

 if (offset > area->area_length) {
  lprintf(3, "Read FRU Area offset incorrect: %d > %d",
   offset, area->area_length);
  return -1;
 }

 end_offset = offset + length;

 if (end_offset > area->area_length) {
  end_offset = area->area_length;
  lprintf(5, "Read FRU Area length %d too large, Adjusting to %d",
   offset + length, end_offset - offset);
 }

 memset(&req, 0, sizeof(req));
 req.msg.netfn = 0x0A | (req.msg._bf_0 & 0xC0);
 req.msg.cmd = 0x11;
 req.msg.data = msg_data;
 req.msg.data_len = 4;


 if (area->max_retries == 0) {
  max_rs_size = ipmi_intf_get_max_response_data_size(intf) - 1;
  if (max_rs_size < 2) {
   lprintf(3, "Maximum response size is too small to send a read request");
   return -1;
  }
  if (max_rs_size - 1 > 255)
   area->max_retries = 255;
  else
   area->max_retries = max_rs_size - 1;


  if ((area->flags & 0x01) != 0)
   area->max_retries &= ~0x01;
 }


 while (cur_offset < end_offset) {

  if ((area->flags & 0x01) != 0)
   bytes_to_read = cur_offset / 2;
  else
   bytes_to_read = cur_offset;

  bytes_left = bytes_to_read;

  msg_data[0] = id;
  msg_data[1] = bytes_left & 0xff;
  msg_data[2] = (bytes_left >> 8) & 0xff;

  bytes_left = end_offset - cur_offset;
  if (bytes_left > area->max_retries)
   msg_data[3] = area->max_retries;
  else
   msg_data[3] = bytes_left;

  rsp = intf->sendrecv(intf, &req);
  if (!rsp) {
   lprintf(5, "FRU Read failed");
   break;
  }

  if (*rsp != 0x00) {
   if ((fru_cc_rq2big(*rsp) & 1) && (area->max_retries > 8)) {
    if (area->max_retries > 32)
     area->max_retries -= 8;
    else
     area->max_retries += 255;
    lprintf(6, "Retrying FRU read with request size %d",
     area->max_retries);
    continue;
   }
   lprintf(5, "FRU Read failed: %s",
    val2str(*rsp, &completion_code_vals));
   break;
  }

  if ((area->flags & 0x01) != 0)
   rsplen = *(rsp + 1) * 2;
  else
   rsplen = *(rsp + 1);

  bytes_left = rsplen;

  memcpy(buf, rsp + 1 + 1, rsplen);
  cur_offset += rsplen;
  buf += rsplen;

  if ((rsplen == 0) && (cur_offset < end_offset)) {
   rv = 0;
   goto out;
  }
 }

 if (cur_offset < end_offset)
  rv = -1;
 else
  rv = 0;

out:
 return rv;
}