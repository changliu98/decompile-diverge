u_int16_t __cdecl concat_hash_string(ndpi_packet_struct *packet, char *buf, u_int8_t client_hash)
{
  u_int32_t len, next_len;
  u_int16_t buf_out_len = 0;
  u_int16_t offset;

  // Base payload length check
  if (packet->payload_packet_len <= 0x1A)
    return 0;

  len = ntohl(*(u_int32_t *)(packet->payload + 22));
  
  // Bounds check for the first string length
  if (packet->payload_packet_len <= 0x1A || len >= (unsigned int)packet->payload_packet_len - 27)
    return 0;

  // Extract first string
  strncpy(buf, (const char *)packet->payload + 26, (unsigned __int16)len);
  buf_out_len = len + 1;
  buf[(unsigned __int16)len] = 59; // ';'

  // Calculate next offset
  offset = ntohl(*(u_int32_t *)&packet->payload[(unsigned __int16)(len + 26)]) + 4 + len + 26;

  // Process 4 alternating fields based on client_hash
  for (int i = 0; i < 4; i++)
  {
    next_len = ntohl(*(u_int32_t *)&packet->payload[offset]);
    
    if (client_hash)
    {
      u_int16_t next_offset = offset + 4;
      // Bounds check
      if (next_offset >= (int)packet->payload_packet_len || next_len >= packet->payload_packet_len - (unsigned int)next_offset - 1)
        return 0;
      
      strncpy(&buf[buf_out_len], (const char *)&packet->payload[next_offset], next_len);
      buf_out_len += next_len + 1;
      buf[buf_out_len - 1] = 59; // ';'
      
      offset = next_len + next_offset;
    }
    else
    {
      offset = next_len + 4 + offset;
    }
  }

  // 5th field
  if ((unsigned __int64)offset + 4 >= packet->payload_packet_len)
    return 0;

  next_len = ntohl(*(u_int32_t *)&packet->payload[offset]);
  if (client_hash)
  {
    u_int16_t next_offset = offset + 4;
    // Bounds check
    if (next_offset >= (int)packet->payload_packet_len || next_len >= packet->payload_packet_len - (unsigned int)next_offset - 1)
      return 0;
      
    strncpy(&buf[buf_out_len], (const char *)&packet->payload[next_offset], next_len);
    buf_out_len += next_len;
    offset = next_len + next_offset;
  }
  else
  {
    offset = next_len + 4 + offset;
  }

  // 6th field
  next_len = ntohl(*(u_int32_t *)&packet->payload[offset]);
  if (!client_hash)
  {
    u_int16_t next_offset = offset + 4;
    // Bounds check
    if (next_offset >= (int)packet->payload_packet_len || next_len >= packet->payload_packet_len - (unsigned int)next_offset - 1)
      return 0;
      
    strncpy(&buf[buf_out_len], (const char *)&packet->payload[next_offset], next_len);
    buf_out_len += next_len;
  }

  return buf_out_len;
}