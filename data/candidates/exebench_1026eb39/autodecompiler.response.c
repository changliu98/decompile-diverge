static void ut32_unpack(unsigned char *buf, unsigned int *val)
{
 unsigned int tmp;

 tmp = buf[3];
 tmp <<= 8;
 tmp += buf[2];
 tmp <<= 8;
 tmp += buf[1];
 tmp <<= 8;
 tmp += buf[0];

 *val = tmp;
}