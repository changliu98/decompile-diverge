void gsm_hex_from_byte(char *hex, int val)
{
    static const char *digits = "0123456789abcdef";

    hex[0] = digits[(val >> 4) & 0xf];
    hex[1] = digits[(val >> 0) & 0xf];
}