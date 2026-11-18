u_int16_t __cdecl concat_hash_string(ndpi_packet_struct *packet, char *buf, u_int8_t client_hash)
{
  unsigned __int16 v3; // cx
  unsigned __int16 v4; // cx
  unsigned __int16 v5; // cx
  unsigned __int16 v6; // cx
  u_int32_t len; // [rsp+Ch] [rbp-24h]
  u_int32_t lena; // [rsp+Ch] [rbp-24h]
  u_int32_t lenb; // [rsp+Ch] [rbp-24h]
  u_int32_t lenc; // [rsp+Ch] [rbp-24h]
  u_int32_t lend; // [rsp+Ch] [rbp-24h]
  u_int32_t lene; // [rsp+Ch] [rbp-24h]
  u_int32_t lenf; // [rsp+Ch] [rbp-24h]
  u_int16_t buf_out_len; // [rsp+12h] [rbp-1Eh]
  u_int16_t offset; // [rsp+14h] [rbp-1Ch]
  u_int16_t offseta; // [rsp+14h] [rbp-1Ch]
  u_int16_t offsetb; // [rsp+14h] [rbp-1Ch]
  u_int16_t offsetc; // [rsp+14h] [rbp-1Ch]
  u_int16_t offsetd; // [rsp+14h] [rbp-1Ch]
  u_int16_t offsete; // [rsp+14h] [rbp-1Ch]
  u_int16_t offsetf; // [rsp+14h] [rbp-1Ch]
  u_int16_t offsetg; // [rsp+14h] [rbp-1Ch]
  u_int16_t offseth; // [rsp+14h] [rbp-1Ch]
  u_int16_t offseti; // [rsp+14h] [rbp-1Ch]
  u_int16_t offsetj; // [rsp+14h] [rbp-1Ch]
  u_int16_t offsetk; // [rsp+14h] [rbp-1Ch]

  if ( packet->payload_packet_len <= 0x1AuLL )
    return 0;
  len = ntohl(*(_DWORD *)(packet->payload + 22));
  if ( packet->payload_packet_len <= 0x1Au || len >= (unsigned int)packet->payload_packet_len - 27 )
    return 0;
  strncpy(buf, (const char *)packet->payload + 26, (unsigned __int16)len);
  buf_out_len = len + 1;
  buf[(unsigned __int16)len] = 59;
  offset = ntohl(*(_DWORD *)&packet->payload[(unsigned __int16)(len + 26)]) + 4 + len + 26;
  lena = ntohl(*(_DWORD *)&packet->payload[offset]);
  if ( client_hash )
  {
    offseta = offset + 4;
    if ( offseta >= (int)packet->payload_packet_len || lena >= packet->payload_packet_len - (unsigned int)offseta - 1 )
      return 0;
    strncpy(&buf[buf_out_len], (const char *)&packet->payload[offseta], lena);
    v3 = lena + buf_out_len;
    buf_out_len += lena + 1;
    buf[v3] = 59;
    offsetb = lena + offseta;
  }
  else
  {
    offsetb = lena + 4 + offset;
  }
  lenb = ntohl(*(_DWORD *)&packet->payload[offsetb]);
  if ( client_hash )
  {
    offsetd = lenb + 4 + offsetb;
  }
  else
  {
    offsetc = offsetb + 4;
    if ( offsetc >= (int)packet->payload_packet_len || lenb >= packet->payload_packet_len - (unsigned int)offsetc - 1 )
      return 0;
    strncpy(&buf[buf_out_len], (const char *)&packet->payload[offsetc], lenb);
    v4 = lenb + buf_out_len;
    buf_out_len += lenb + 1;
    buf[v4] = 59;
    offsetd = lenb + offsetc;
  }
  lenc = ntohl(*(_DWORD *)&packet->payload[offsetd]);
  if ( client_hash )
  {
    offsete = offsetd + 4;
    if ( offsete >= (int)packet->payload_packet_len || lenc >= packet->payload_packet_len - (unsigned int)offsete - 1 )
      return 0;
    strncpy(&buf[buf_out_len], (const char *)&packet->payload[offsete], lenc);
    v5 = lenc + buf_out_len;
    buf_out_len += lenc + 1;
    buf[v5] = 59;
    offsetf = lenc + offsete;
  }
  else
  {
    offsetf = lenc + 4 + offsetd;
  }
  lend = ntohl(*(_DWORD *)&packet->payload[offsetf]);
  if ( client_hash )
  {
    offseth = lend + 4 + offsetf;
  }
  else
  {
    offsetg = offsetf + 4;
    if ( offsetg >= (int)packet->payload_packet_len || lend >= packet->payload_packet_len - (unsigned int)offsetg - 1 )
      return 0;
    strncpy(&buf[buf_out_len], (const char *)&packet->payload[offsetg], lend);
    v6 = lend + buf_out_len;
    buf_out_len += lend + 1;
    buf[v6] = 59;
    offseth = lend + offsetg;
  }
  if ( (unsigned __int64)offseth + 4 >= packet->payload_packet_len )
    return 0;
  lene = ntohl(*(_DWORD *)&packet->payload[offseth]);
  if ( client_hash )
  {
    offseti = offseth + 4;
    if ( offseti >= (int)packet->payload_packet_len || lene >= packet->payload_packet_len - (unsigned int)offseti - 1 )
      return 0;
    strncpy(&buf[buf_out_len], (const char *)&packet->payload[offseti], lene);
    buf_out_len += lene;
    offsetj = lene + offseti;
  }
  else
  {
    offsetj = lene + 4 + offseth;
  }
  lenf = ntohl(*(_DWORD *)&packet->payload[offsetj]);
  if ( !client_hash )
  {
    offsetk = offsetj + 4;
    if ( offsetk >= (int)packet->payload_packet_len || lenf >= packet->payload_packet_len - (unsigned int)offsetk - 1 )
      return 0;
    strncpy(&buf[buf_out_len], (const char *)&packet->payload[offsetk], lenf);
    buf_out_len += lenf;
  }
  return buf_out_len;
}