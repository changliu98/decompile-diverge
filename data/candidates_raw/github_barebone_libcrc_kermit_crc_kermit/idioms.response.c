unsigned short calculate_crc(void *data, long data_len)
{
  unsigned int crc;
  unsigned char *buf;
  long i;
  if (crc_tab_init == 0)
    init_crc_tab();
  crc = 0;
  for (buf = (unsigned char *)data, i = 0; i < data_len; i++)
    crc = (crc_tab[(crc ^ *buf++) & 0xff] ^ (crc >> 8));
  return (crc & 0xff) | ((crc & 0xff00) << 8);
}