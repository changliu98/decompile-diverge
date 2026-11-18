int
read_fru_area(ipmi_intf * intf, fru_info * fru,
       uint8_t id, uint32_t offset, uint32_t length, uint8_t * frubuf)
{
  unsigned short size;
  uint32_t finish;
  uint8_t msg_data[4];
  ipmi_rq req;
  ipmi_rs * rsp;
  uint32_t rsp_size;

  if (offset > fru->size)
    {
      lprintf(3, "Read FRU Area offset incorrect: %d > %d",
       offset, fru->size);
      return (-1);
    }

  finish = offset + length;
  if (finish > fru->size)
    {
      finish = fru->size;
      lprintf(5, "Read FRU Area length %d too large, Adjusting to %d",
       offset + length, finish - offset);
    }

  memset(&req, 0, sizeof(req));
  req.msg.netfn = 0x0a;
  req.msg.cmd = 0x11;
  req.msg.data = msg_data;
  req.msg.data_len = 4;

  if (fru->max_read_size == 0)
    {
      unsigned short max_rs_size = ipmi_intf_get_max_response_data_size(intf);
      max_rs_size--;
      if (max_rs_size < 2)
 {
   lprintf(3, "Maximum response size is too small to send a read request");
   return (-1);
 }
      if (max_rs_size > 255)
 max_rs_size = 255;
      fru->max_read_size = max_rs_size;
      if (fru->access)
 fru->max_read_size &= 0xfe;
    }

  do
    {
      if (fru->access)
 size = (offset >> 1) & 0xffff;
      else
 size = offset & 0xffff;
      msg_data[1] = size & 0xff;
      msg_data[2] = (size >> 8) & 0xff;
      if ((finish - offset) > fru->max_read_size)
 msg_data[3] = fru->max_read_size;
      else
 msg_data[3] = finish - offset;
      msg_data[0] = id;

      rsp = intf->sendrecv(intf, &req);
      if (!rsp)
 {
   lprintf(5, "FRU Read failed");
   break;
 }

      if (rsp->ccode)
 {
   if (fru_cc_rq2big(rsp->ccode) && (fru->max_read_size > 8))
     {
       if (fru->max_read_size > 32)
  fru->max_read_size -= 8;
       else
  fru->max_read_size -= 7;
       lprintf(6, "Retrying FRU read with request size %d",
        fru->max_read_size);
       continue;
     }
   lprintf(5, "FRU Read failed: %s",
    val2str(rsp->ccode, completion_code_vals));
   break;
 }

      if (fru->access)
 rsp_size = rsp->data[0] << 1;
      else
 rsp_size = rsp->data[0];
      memcpy(frubuf, rsp->data + 1, rsp_size);
      offset += rsp_size;
      frubuf += rsp_size;

      if ((rsp_size == 0) && (offset < finish))
 return (0);
    }
  while (offset < finish);

  if (offset < finish)
    return (-1);
  else
    return (0);
}