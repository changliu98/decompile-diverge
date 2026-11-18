int send_cw(int sock, struct cwiter *cw)
{
  int ret = -1;
  ret = send(sock, (void *)cw, sizeof(struct cwiter), 0);
  if (ret == -1){
    syslog(3,"ca.so: Send cw failed %d", (*__errno_location ()));
    return 0;
  }
  return 1;
}