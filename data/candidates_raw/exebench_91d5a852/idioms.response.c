void int2bytes(int val, char *bytes)
{
  bytes[0] = (char)(val & 0xff);
  bytes[1] = (char)((val >> 8) & 0xff);
  bytes[2] = (char)((val >> 16) & 0xff);
  bytes[3] = (char)(val >> 24);
}