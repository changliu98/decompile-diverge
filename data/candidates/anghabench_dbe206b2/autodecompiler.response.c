int get_opcode(unsigned char *buf, int *op)
{
 int len;

 if ((buf[0] & 0x0f) == 0x0f) {
  *op = *(unsigned short *)buf;
  len = 2;
 } else {
  *op = buf[0];
  len = 1;
 }
 return len;
}