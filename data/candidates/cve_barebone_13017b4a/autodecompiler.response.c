static int jpeg_size(unsigned char *buf, unsigned int size,
                                unsigned int *w, unsigned int *h)
{
    int pos = 0;
    unsigned short block_len;
    int ret;

    if ((pos + 3 < size) &&
            (buf[pos] == 0xFF) && (buf[pos + 1] == 0xD8) &&
            (buf[pos + 2] == 0xFF) && (buf[pos + 3] == 0xE0)) {
        pos += 4;

        if ((pos + 6 < size) &&
                (buf[pos + 2] == 0x4A) && (buf[pos + 3] == 0x46) &&
                (buf[pos + 4] == 0x49) && (buf[pos + 5] == 0x46) &&
                (buf[pos + 6] == 0x00)) {

            block_len = buf[pos] * 256 + buf[pos + 1];

            while (pos < size) {
                pos += block_len;

                if (pos + 1 >= size) {
                    ret = -1;
                    break;
                }

                if (buf[pos] != 0xFF) {
                    ret = -1;
                    break;
                }

                if (buf[pos + 1] == 0xC0) {

                    *h = buf[pos + 5] * 256 + buf[pos + 6];
                    *w = buf[pos + 7] * 256 + buf[pos + 8];
                    ret = 0;
                    break;
                } else {
                    pos += 2;
                    block_len = buf[pos] * 256 + buf[pos + 1];
                }
            }
        } else {
            ret = -1;
        }
    } else {
        ret = -1;
    }

    return ret;
}