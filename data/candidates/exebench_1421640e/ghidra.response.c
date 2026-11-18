void encode_vector(char *c,int x,int y)

{
  int y_local;
  int x_local;
  char *c_local;
  
  *c = (char)(y >> 5) + ' ';
  c[1] = ((byte)y & 0x1f) + 0x60;
  c[2] = (char)(x >> 5) + ' ';
  c[3] = ((byte)x & 0x1f) + 0x40;
  c[4] = '\0';
  return;
}