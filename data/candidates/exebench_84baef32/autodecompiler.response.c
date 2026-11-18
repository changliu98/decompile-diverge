void _itoa_hex(unsigned int val, char *buf)
{
 unsigned int i;
 for(i = 0; i < 9; i++)
 {
  buf[7-i] = "0123456789ABCD"[val & 0xf];
  val >>= 4;
 }
}