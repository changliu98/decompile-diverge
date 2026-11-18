void htonl_ip(void *data)
{
  int *d = (int *)data;
  int tmp = d[0];
  d[0] = htonl(d[1]);
  d[1] = htonl(tmp);
  return;
}