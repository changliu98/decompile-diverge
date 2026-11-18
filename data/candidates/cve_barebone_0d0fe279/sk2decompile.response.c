static unsigned short concat_hash_string(packet_t *packet,
                                         unsigned char *hash_string,
                                         unsigned char is_hash) {
  unsigned short offset, len = 0;
  unsigned int hash_len;
  unsigned int str_len;
  if (packet->length < 27) return 0;
  hash_len = ntohl(*(unsigned int *)(packet->data + 22));
  if (packet->length < 27 || hash_len > packet->length - 27) return 0;
  strncpy((char *)hash_string, (char *)(packet->data + 26), hash_len);
  len += hash_len;
  hash_string[len++] = ';';
  offset = 26 + hash_len + 4;
  str_len = ntohl(*(unsigned int *)(packet->data + offset));
  if (is_hash) {
    offset += 4;
    if (offset >= packet->length || str_len > packet->length - offset - 1)
      return 0;
    strncpy((char *)hash_string + len, (char *)(packet->data + offset), str_len);
    len += str_len;
    hash_string[len++] = ';';
    offset += str_len;
  } else
    offset += str_len;
  str_len = ntohl(*(unsigned int *)(packet->data + offset));
  if (is_hash) {
    offset += 4;
    if (offset >= packet->length || str_len > packet->length - offset - 1)
      return 0;
    strncpy((char *)hash_string + len, (char *)(packet->data + offset), str_len);
    len += str_len;
    hash_string[len++] = ';';
    offset += str_len;
  } else
    offset += str_len;
  str_len = ntohl(*(unsigned int *)(packet->data + offset));
  if (is_hash) {
    offset += 4;
    if (offset >= packet->length || str_len > packet->length - offset - 1)
      return 0;
    strncpy((char *)hash_string + len, (char *)(packet->data + offset), str_len);
    len += str_len;
    hash_string[len++] = ';';
    offset += str_len;
  } else
    offset += str_len;
  str_len = ntohl(*(unsigned int *)(packet->data + offset));
  if (is_hash) {
    offset += 4;
    if (offset >= packet->length || str_len > packet->length - offset - 1)
      return 0;
    strncpy((char *)hash_string + len, (char *)(packet->data + offset), str_len);
    len += str_len;
    hash_string[len++] = ';';
    offset += str_len;
  } else
    offset += str_len;
  if (offset + 4 >= packet->length) return 0;
  str_len = ntohl(*(unsigned int *)(packet->data + offset));
  if (is_hash) {
    offset += 4;
    if (offset >= packet->length || str_len > packet->length - offset - 1)
      return 0;
    strncpy((char *)hash_string + len, (char *)(packet->data + offset), str_len);
    len += str_len;
    offset += str_len;
  } else
    offset += str_len;
  str_len = ntohl(*(unsigned int *)(packet->data + offset));
  if (!is_hash) {
    offset += 4;
    if (offset >= packet->length || str_len > packet->length - offset - 1)
      return 0;
    strncpy((char *)hash_string + len, (char *)(packet->data + offset), str_len);
    len += str_len;
  }
  return len;
}