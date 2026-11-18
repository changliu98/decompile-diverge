void
gsm_hex_from_byte(char *to, int b)
{
    to[0] = "0123456789abcdef"[(b >> 4) & 0xF];
    to[1] = "0123456789abcdef"[(b & 0xF)];
}