int jpeg_size(const unsigned char *data, int data_size, int *width, int *height)
{
    unsigned int offset = 0;
    unsigned int block_length = 0;

    if (data_size < 4 || data[0] != 0xFF || data[1] != 0xD8 || data[2] != 0xFF || data[3] != 0xE0)
        return -1;

    offset += 4;

    if (data_size < 11 || data[6] != 'J' || data[7] != 'F' || data[8] != 'I' || data[9] != 'F' || data[10] != 0)
        return -1;

    block_length = data[4] * 256 + data[5];

    while (offset < (unsigned int)data_size)
    {
        if (offset + block_length + 2 > (unsigned int)data_size)
            return -1;

        if (data[offset + block_length] != 0xFF)
            return -1;

        if (data[offset + block_length + 1] == 0xC0)
        {
            *height = data[offset + block_length + 5] * 256 + data[offset + block_length + 6];
            *width = data[offset + block_length + 7] * 256 + data[offset + block_length + 8];
            return 0;
        }

        offset += block_length + 2;
        block_length = data[offset] * 256 + data[offset + 1];
    }

    return -1;
}