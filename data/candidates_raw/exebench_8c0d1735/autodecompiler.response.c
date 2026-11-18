static int
b64_byte_to_char(int b, char *c)
{
    *c = ((b & 0x5f) + 0x30);
    return b;
}