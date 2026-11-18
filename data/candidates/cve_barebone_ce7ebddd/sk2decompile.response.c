void delete_buff_tail(t_client *client, int size) {
  int len;
  len = strlen(client->buff->data);
  if (len >= size) {
    client->buff->data[len - size] = '\0';
    client->buff_size += size;
  }
}