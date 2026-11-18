static int
dv_write_ssyb_id(unsigned char scs, unsigned char gl, unsigned char *out)
{
 switch (scs) {
 case 0x00:
 case 0x06:
  out[0] = 0x00 | (gl << 7) | 0x0f;
  break;
 case 0x0b:
  out[0] = 0x7f | (gl << 7);
  break;
 default:
  out[0] = 0x00 | (gl << 7) | 0x0f;
 }
 out[1] = 0xf0 | (scs & 0x0f);
 out[2] = 0xff;

 return (3);
}