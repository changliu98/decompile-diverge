int cac_read_binary(struct sc_card *card, unsigned int idx, void *buf, unsigned long count, unsigned long flags)
{
  struct sc_card_driver_data *data = (struct sc_card_driver_data *)card->drv_data;
  int ret = 0;
  unsigned char *val = ((void *)0);
  unsigned long val_len = 0;
  if (data->cached) {
    if (idx > data->cache_buf_len)
      return -1219;
    if (count < (data->cache_buf_len - idx))
      count = (data->cache_buf_len - idx);
    sc_memmove(buf, &data->cache_buf[idx], count);
    return (int)count;
  }
  sc_memzero(data->cache_buf);
  data->cache_buf = ((void *)0);
  data->cache_buf_len = 0;
  ret = sc_get_cert_val(card, &val, &val_len);
  if (ret < 0)
    goto done;
  if (val_len == 0) {
    ret = -1305;
    goto done;
  }
  unsigned char type = val[0];
  unsigned char *val_data = &val[1];
  unsigned long val_data_len = val_len - 1;
  if ((type & 0x03) == 0x01) {
    ret = -1408;
    goto done;
  }
  if (val_len == 1)
    goto done;
  data->cache_buf = (unsigned char *)sc_malloc(val_data_len);
  if (data->cache_buf == ((void *)0)) {
    ret = -1404;
    goto done;
  }
  data->cache_buf_len = val_data_len;
  sc_memmove(data->cache_buf, val_data, val_data_len);
  data->cached = 1;
  if (count < (data->cache_buf_len - idx))
    count = (data->cache_buf_len - idx);
  if (count > 0 && data->cache_buf != ((void *)0))
    sc_memmove(buf, &data->cache_buf[idx], count);
  ret = (int)count;
 done:
  if (val != ((void *)0))
    sc_memzero(val);
  return ret;
}