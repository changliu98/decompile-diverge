void to_hex(long x, char* c)
{
 int i;
 char h[16] = "0123456789ABCDEF";

 for (i=3; i>=0; i--)
 {
  c[i] = h[x % 16];
  x >>= 4;
 }
 c[4] = '\0';
}