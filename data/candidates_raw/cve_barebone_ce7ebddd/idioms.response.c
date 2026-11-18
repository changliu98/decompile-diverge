void buff_remove(struct buffheader *buf, int len)
{
  int i = buff_strlen(buf->bh_curr->b_str);
  if (i >= len) {
    buf->bh_curr->b_str[i - len] = '\0';
    buf->bh_space += len;
  }
}