static unsigned short
get_client_info(struct dhcp_packet *packet, char *info, unsigned char client_hash)
{
 unsigned int len;
 unsigned short pos = 22;
 unsigned short info_pos = 0;
 unsigned short ret;

 if (pos + sizeof(len) >= packet->hlen)
  goto invalid_payload;

 len = ntohl(*((unsigned int *) &packet->data[pos]));
 pos += sizeof(len);

 if (pos >= packet->hlen || len >= packet->hlen - pos - 1)
  goto invalid_payload;

 strncpy(info, &packet->data[pos], info_pos = len);
 info[++info_pos] = ';';
 pos += len;

 len = ntohl(*((unsigned int *) &packet->data[pos]));
 pos += sizeof(len) + len;

 if (client_hash) {
  pos += sizeof(len);

  if (pos >= packet->hlen || len >= packet->hlen - pos - 1)
   goto invalid_payload;

  strncpy(&info[info_pos], &packet->data[pos], len);
  info_pos += len;
  info[++info_pos] = ';';
  pos += len;
 } else
  pos += sizeof(len) + len;

 len = ntohl(*((unsigned int *) &packet->data[pos]));

 if (!client_hash) {
  pos += sizeof(len);

  if (pos >= packet->hlen || len >= packet->hlen - pos - 1)
   goto invalid_payload;

  strncpy(&info[info_pos], &packet->data[pos], len);
  info_pos += len;
  info[++info_pos] = ';';
  pos += len;
 } else
  pos += sizeof(len) + len;

 len = ntohl(*((unsigned int *) &packet->data[pos]));

 if (client_hash) {
  pos += sizeof(len);

  if (pos >= packet->hlen || len >= packet->hlen - pos - 1)
   goto invalid_payload;

  strncpy(&info[info_pos], &packet->data[pos], len);
  info_pos += len;
  pos += len;
 } else
  pos += sizeof(len) + len;

 len = ntohl(*((unsigned int *) &packet->data[pos]));

 if (!client_hash) {
  pos += sizeof(len);

  if (pos >= packet->hlen || len >= packet->hlen - pos - 1)
   goto invalid_payload;

  strncpy(&info[info_pos], &packet->data[pos], len);
  info_pos += len;
  pos += len;
 } else
  pos += sizeof(len) + len;

 if (pos + sizeof(len) >= packet->hlen)
  goto invalid_payload;

 len = ntohl(*((unsigned int *) &packet->data[pos]));

 if (client_hash) {
  pos += sizeof(len);

  if (pos >= packet->hlen || len >= packet->hlen - pos - 1)
   goto invalid_payload;

  strncpy(&info[info_pos], &packet->data[pos], len);
  info_pos += len;
  pos += len;
 } else
  pos += sizeof(len) + len;

 len = ntohl(*((unsigned int *) &packet->data[pos]));

 if (!client_hash) {
  pos += sizeof(len);

  if (pos >= packet->hlen || len >= packet->hlen - pos - 1)
   goto invalid_payload;

  strncpy(&info[info_pos], &packet->data[pos], len);
  info_pos += len;
  pos += len;
 } else
  pos += sizeof(len) + len;

 ret = info_pos;
 return ret;

invalid_payload:
 ret = 0;
 return ret;
}