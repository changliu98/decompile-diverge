int openI2CBus(ser_device_t *dev, char *name)
{
 int ret;

 dev->fd = open(name, 2);
 if (dev->fd < 0) {
  ret = 1;
 } else {
  ret = 0;
 }

 return ret;
}