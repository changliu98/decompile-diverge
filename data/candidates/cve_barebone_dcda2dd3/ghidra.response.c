int read_fru_area(ipmi_intf *intf,fru_info *fru,uint8_t id,uint32_t offset,uint32_t length,
                 uint8_t *frubuf)

{
  _Bool _Var1;
  uint16_t uVar2;
  ushort uVar3;
  ipmi_rs *piVar4;
  char *pcVar5;
  uint local_70;
  undefined2 local_6c;
  uint16_t max_rs_size;
  uint8_t msg_data [4];
  ipmi_rq req;
  ipmi_rs *rsp;
  uint32_t finish;
  uint32_t tmp;
  uint32_t off;
  uint8_t *frubuf_local;
  uint32_t length_local;
  uint32_t offset_local;
  uint8_t id_local;
  fru_info *fru_local;
  ipmi_intf *intf_local;
  int local_c;
  
  if (fru->size < offset) {
    lprintf(3,"Read FRU Area offset incorrect: %d > %d",(ulong)offset,(ulong)fru->size);
    local_c = -1;
  }
  else {
    finish = offset + length;
    if (fru->size < finish) {
      finish = (uint32_t)fru->size;
      lprintf(5,"Read FRU Area length %d too large, Adjusting to %d",(ulong)(offset + length),
              (ulong)(finish - offset));
    }
    memset(&req,0,0x10);
    req.msg.netfn = '\n';
    req.msg.cmd = '\x11';
    req.msg.data = msg_data;
    req.msg.data_len = 4;
    off = offset;
    frubuf_local = frubuf;
    if (fru->max_read_size == '\0') {
      uVar2 = ipmi_intf_get_max_response_data_size(intf);
      uVar3 = uVar2 - 1;
      if (uVar3 < 2) {
        lprintf(3,"Maximum response size is too small to send a read request");
        return -1;
      }
      if ((int)(uVar3 - 1) < 0x100) {
        fru->max_read_size = (char)uVar3 + 0xff;
      }
      else {
        fru->max_read_size = 0xff;
      }
      if (fru->access != 0) {
        fru->max_read_size = fru->max_read_size & 0xfe;
      }
    }
    do {
      if (fru->access == 0) {
        local_6c = (undefined2)off;
      }
      else {
        local_6c = (undefined2)(off >> 1);
      }
      msg_data[1] = (uint8_t)local_6c;
      msg_data[2] = (uint8_t)((ushort)local_6c >> 8);
      if ((uint)fru->max_read_size < finish - off) {
        msg_data[3] = fru->max_read_size;
      }
      else {
        msg_data[3] = (uint8_t)(finish - off);
      }
      msg_data[0] = id;
      piVar4 = (*intf->sendrecv)(intf,&req);
      if (piVar4 == (ipmi_rs *)0x0) {
        lprintf(5,"FRU Read failed");
        break;
      }
      if (piVar4->ccode == '\0') {
        if (fru->access == 0) {
          local_70 = (uint)piVar4->data[0];
        }
        else {
          local_70 = (uint)piVar4->data[0] << 1;
        }
        memcpy(frubuf_local,piVar4->data + 1,(ulong)local_70);
        off = local_70 + off;
        frubuf_local = frubuf_local + local_70;
        if ((local_70 == 0) && (off < finish)) {
          return 0;
        }
      }
      else {
        _Var1 = fru_cc_rq2big((uint)piVar4->ccode);
        if ((!_Var1) || (fru->max_read_size < 9)) {
          pcVar5 = val2str((uint)piVar4->ccode,completion_code_vals);
          lprintf(5,"FRU Read failed: %s",pcVar5);
          break;
        }
        if (fru->max_read_size < 0x21) {
          fru->max_read_size = fru->max_read_size + 0xff;
        }
        else {
          fru->max_read_size = fru->max_read_size + 0xf8;
        }
        lprintf(6,"Retrying FRU read with request size %d",(ulong)fru->max_read_size);
      }
    } while (off < finish);
    if (off < finish) {
      local_c = -1;
    }
    else {
      local_c = 0;
    }
  }
  return local_c;
}