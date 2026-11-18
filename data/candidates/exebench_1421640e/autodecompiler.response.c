void
encode_vector(char *buf, int n, int m)
{
 buf[0] = (m >> 5) + ' ';
 buf[1] = (m & 0x1f) + 'a' - 1;
 buf[2] = (n >> 5) + ' ';
 buf[3] = (n & 0x1f) + 'A' - 1;
 buf[4] = '\0';
}