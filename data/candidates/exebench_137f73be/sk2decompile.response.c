int I2CSensor_Read(struct I2CSensorDevice *d, unsigned char addr,
                   unsigned char reg, unsigned char *data, int len) {
  int r;
  r = ioctl(d->fd, 0x0703, addr);
  if (r < 0) return 3;
  if (write(d->fd, &reg, 1) != 1) return 3;
  if (read(d->fd, data, len) != len) return 3;
  return 0;
}