void
encaps(char *buf, char *data, int len)
{
    while (len--) {
 *buf++ = *data++;
 if (*data == DLE)
     *buf++ = DLE;
    }
}