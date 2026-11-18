unsigned short concat_hash_string(struct ndpi_packet_struct *packet, char *buf, unsigned char client_hash) {
  unsigned short offset = 22;
  unsigned short buf_out_len = 0;
  unsigned int len;


  if(offset >= packet->payload_packet_len)
    return 0;

  len = ntohl(*(uint32_t *)&packet->payload[offset]);
  offset += 4;

  if(offset >= packet->payload_packet_len)
    return 0;

  if(len > packet->payload_packet_len - offset - 1)
    return 0;

  strncpy(buf + buf_out_len, packet->payload + offset, len);
  buf_out_len += len;
  buf[buf_out_len] = ';';
  buf_out_len++;
  offset += len;

  len = ntohl(*(uint32_t *)&packet->payload[offset]);
  offset += 4;

  if(client_hash) {
    if(offset >= packet->payload_packet_len)
      return 0;

    if(len > packet->payload_packet_len - offset - 1)
      return 0;

    strncpy(buf + buf_out_len, packet->payload + offset, len);
    buf_out_len += len;
    buf[buf_out_len] = ';';
    buf_out_len++;
    offset += len;
  } else {
    offset += len;
  }

  len = ntohl(*(uint32_t *)&packet->payload[offset]);
  offset += 4;

  if(client_hash) {
    if(offset >= packet->payload_packet_len)
      return 0;

    if(len > packet->payload_packet_len - offset - 1)
      return 0;

    strncpy(buf + buf_out_len, packet->payload + offset, len);
    buf_out_len += len;
    buf[buf_out_len] = ';';
    buf_out_len++;
    offset += len;
  } else {
    offset += len;
  }

  len = ntohl(*(uint32_t *)&packet->payload[offset]);
  offset += 4;

  if(client_hash) {
    if(offset >= packet->payload_packet_len)
      return 0;

    if(len > packet->payload_packet_len - offset - 1)
      return 0;

    strncpy(buf + buf_out_len, packet->payload + offset, len);
    buf_out_len += len;
    buf[buf_out_len] = ';';
    buf_out_len++;
    offset += len;
  } else {
    offset += len;
  }

  len = ntohl(*(uint32_t *)&packet->payload[offset]);
  offset += 4;

  if(client_hash) {
    if(offset >= packet->payload_packet_len)
      return 0;

    if(len > packet->payload_packet_len - offset - 1)
      return 0;

    strncpy(buf + buf_out_len, packet->payload + offset, len);
    buf_out_len += len;
    buf[buf_out_len] = ';';
    buf_out_len++;
    offset += len;
  } else {
    offset += len;
  }

  if(offset + 4 >= packet->payload_packet_len)
    return 0;

  len = ntohl(*(uint32_t *)&packet->payload[offset]);
  offset += 4;

  if(client_hash) {
    if(offset >= packet->payload_packet_len)
      return 0;

    if(len > packet->payload_packet_len - offset - 1)
      return 0;

    strncpy(buf + buf_out_len, packet->payload + offset, len);
    buf_out_len += len;
    offset += len;
  } else {
    offset += len;
  }

  len = ntohl(*(uint32_t *)&packet->payload[offset]);
  offset += 4;

  if(client_hash) {
    if(offset >= packet->payload_packet_len)
      return 0;

    if(len > packet->payload_packet_len - offset - 1)
      return 0;

    strncpy(buf + buf_out_len, packet->payload + offset, len);
    buf_out_len += len;
    offset += len;
  } else {
    offset += len;
  }

  return buf_out_len;
}