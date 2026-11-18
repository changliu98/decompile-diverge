void
insert_dle(char *buf, char *data, int len)
{
    while (len--) {
 *buf++ = *data++;
 if (*data == DLE)
     *buf++ = DLE;
    }
}