static void write_le32(int val, char *buf)
{
 buf[0] = (char)(val & 0xff);
 buf[1] = (char)((val >> 8) & 0xff);
 buf[2] = (char)((val >> 16) & 0xff);
 buf[3] = (char)((val >> 24) & 0xff);
}