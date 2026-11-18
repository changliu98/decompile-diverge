pj_status_t pjstun_parse_msg(void *buf,pj_size_t buf_len,pjstun_msg *msg)

{
  pj_uint16_t pVar1;
  uint uVar2;
  pjstun_attr_hdr **pppVar3;
  pj_uint16_t attr_type;
  pj_uint32_t len;
  pjstun_attr_hdr **attr;
  char *p_attr;
  pj_uint16_t msg_len;
  pj_uint16_t msg_type;
  pjstun_msg *msg_local;
  pj_size_t buf_len_local;
  void *buf_local;
  pj_status_t local_c;
  
  msg->hdr = buf;
  pVar1 = pj_ntohs(msg->hdr->type);
  uVar2 = (uint)pVar1;
  if (((uVar2 - 1 < 2) || (uVar2 - 0x101 < 2)) || (uVar2 == 0x111 || uVar2 == 0x112)) {
    msg_len = pj_ntohs(msg->hdr->length);
    if ((ulong)msg_len == buf_len - 0x14) {
      msg->attr_count = 0;
      p_attr = (char *)((long)buf + 0x14);
      while (msg_len != 0) {
        pppVar3 = msg->attr + msg->attr_count;
        *pppVar3 = (pjstun_attr_hdr *)p_attr;
        pVar1 = pj_ntohs((*pppVar3)->length);
        uVar2 = pVar1 + 7 & 0xfffffffc;
        if (msg_len < uVar2) {
          return 0x4e204;
        }
        pj_ntohs((*pppVar3)->type);
        msg_len = msg_len - (short)uVar2;
        p_attr = p_attr + uVar2;
        msg->attr_count = msg->attr_count + 1;
      }
      local_c = 0;
    }
    else {
      local_c = 0x4e203;
    }
  }
  else {
    local_c = 0x4e202;
  }
  return local_c;
}