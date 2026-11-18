static int jpeg_size(unsigned char *data, int len, int *start, int *end) {
    int i = 0;
    unsigned short tmp;

    while (i < len) {
        if (data[i] == 0xff && data[i + 1] == 0xd8 && data[i + 2] == 0xff &&
            data[i + 3] == 0xe0) {
            i += 4;
            while (data[i] == 0xff && data[i + 1] == 0xd8 &&
                   data[i + 2] == 0xff && data[i + 3] == 0xe1) {
                i += 4;
                *start = i;
                *end = i + 1;
                i = -1;
            }
        }
        if (data[i] == 0xff && data[i + 1] == 0xd8) {
            tmp = data[i] << 8;
            tmp += data[i + 1];
            *start = tmp;
            tmp = data[i + 2] << 8;
            tmp += data[i + 3];
            *end = tmp;
            i = -1;
        }
        i++;
    }
    return 0;
}