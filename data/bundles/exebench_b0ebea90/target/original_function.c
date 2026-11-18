int sendcw(int fd, unsigned char *buff) {
  ;
  if ( send(fd,buff, 18, 0) == -1 ) {
   {syslog(LOG_ERR, "ca.so: Send cw failed %d", errno);};
    return 0;
  }
  return 1;
}