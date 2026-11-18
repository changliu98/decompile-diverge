u_int16_t concat_hash_string(ndpi_packet_struct *packet,char *buf,u_int8_t client_hash)

{
  short sVar1;
  ushort uVar2;
  ushort uVar3;
  uint32_t uVar4;
  u_int32_t len;
  u_int16_t buf_out_len;
  u_int16_t offset;
  u_int8_t client_hash_local;
  char *buf_local;
  ndpi_packet_struct *packet_local;
  
  if (((0x1a < packet->payload_packet_len) &&
      (uVar4 = ntohl(*(uint32_t *)(packet->payload + 0x16)), 0x1a < packet->payload_packet_len)) &&
     (uVar4 < packet->payload_packet_len - 0x1b)) {
    uVar2 = (ushort)uVar4;
    strncpy(buf,(char *)(packet->payload + 0x1a),(ulong)(uVar4 & 0xffff));
    buf_out_len = uVar2 + 1;
    buf[uVar2] = ';';
    uVar4 = ntohl(*(uint32_t *)(packet->payload + (ushort)(uVar2 + 0x1a)));
    uVar2 = uVar2 + 0x1a + (short)uVar4 + 4;
    uVar4 = ntohl(*(uint32_t *)(packet->payload + uVar2));
    sVar1 = (short)uVar4;
    if (client_hash == '\0') {
      offset = uVar2 + sVar1 + 4;
    }
    else {
      uVar2 = uVar2 + 4;
      if (packet->payload_packet_len <= uVar2) {
        return 0;
      }
      if (((uint)packet->payload_packet_len - (uint)uVar2) - 1 <= uVar4) {
        return 0;
      }
      strncpy(buf + buf_out_len,(char *)(packet->payload + uVar2),(ulong)uVar4);
      uVar3 = buf_out_len + sVar1;
      buf_out_len = uVar3 + 1;
      buf[uVar3] = ';';
      offset = uVar2 + sVar1;
    }
    uVar4 = ntohl(*(uint32_t *)(packet->payload + offset));
    sVar1 = (short)uVar4;
    if (client_hash == '\0') {
      uVar2 = offset + 4;
      if (packet->payload_packet_len <= uVar2) {
        return 0;
      }
      if (((uint)packet->payload_packet_len - (uint)uVar2) - 1 <= uVar4) {
        return 0;
      }
      strncpy(buf + buf_out_len,(char *)(packet->payload + uVar2),(ulong)uVar4);
      uVar3 = buf_out_len + sVar1;
      buf_out_len = uVar3 + 1;
      buf[uVar3] = ';';
      offset = uVar2 + sVar1;
    }
    else {
      offset = offset + sVar1 + 4;
    }
    uVar4 = ntohl(*(uint32_t *)(packet->payload + offset));
    sVar1 = (short)uVar4;
    if (client_hash == '\0') {
      offset = offset + sVar1 + 4;
    }
    else {
      uVar2 = offset + 4;
      if (packet->payload_packet_len <= uVar2) {
        return 0;
      }
      if (((uint)packet->payload_packet_len - (uint)uVar2) - 1 <= uVar4) {
        return 0;
      }
      strncpy(buf + buf_out_len,(char *)(packet->payload + uVar2),(ulong)uVar4);
      uVar3 = buf_out_len + sVar1;
      buf_out_len = uVar3 + 1;
      buf[uVar3] = ';';
      offset = uVar2 + sVar1;
    }
    uVar4 = ntohl(*(uint32_t *)(packet->payload + offset));
    sVar1 = (short)uVar4;
    if (client_hash == '\0') {
      uVar2 = offset + 4;
      if (packet->payload_packet_len <= uVar2) {
        return 0;
      }
      if (((uint)packet->payload_packet_len - (uint)uVar2) - 1 <= uVar4) {
        return 0;
      }
      strncpy(buf + buf_out_len,(char *)(packet->payload + uVar2),(ulong)uVar4);
      uVar3 = buf_out_len + sVar1;
      buf_out_len = uVar3 + 1;
      buf[uVar3] = ';';
      offset = uVar2 + sVar1;
    }
    else {
      offset = offset + sVar1 + 4;
    }
    if ((ulong)offset + 4 < (ulong)packet->payload_packet_len) {
      uVar4 = ntohl(*(uint32_t *)(packet->payload + offset));
      sVar1 = (short)uVar4;
      if (client_hash == '\0') {
        offset = offset + sVar1 + 4;
      }
      else {
        uVar2 = offset + 4;
        if (packet->payload_packet_len <= uVar2) {
          return 0;
        }
        if (((uint)packet->payload_packet_len - (uint)uVar2) - 1 <= uVar4) {
          return 0;
        }
        strncpy(buf + buf_out_len,(char *)(packet->payload + uVar2),(ulong)uVar4);
        buf_out_len = buf_out_len + sVar1;
        offset = uVar2 + sVar1;
      }
      uVar4 = ntohl(*(uint32_t *)(packet->payload + offset));
      if (client_hash == '\0') {
        uVar2 = offset + 4;
        if (packet->payload_packet_len <= uVar2) {
          return 0;
        }
        if (((uint)packet->payload_packet_len - (uint)uVar2) - 1 <= uVar4) {
          return 0;
        }
        strncpy(buf + buf_out_len,(char *)(packet->payload + uVar2),(ulong)uVar4);
        buf_out_len = buf_out_len + (short)uVar4;
      }
      return buf_out_len;
    }
  }
  return 0;
}