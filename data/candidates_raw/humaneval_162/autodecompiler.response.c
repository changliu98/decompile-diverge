char *get_hash(char *str)
{
    int i, j;
    unsigned int byte, crc, len;
    char *hash;

    if (strlen(str) == 0) {
        hash = strdup("None");
    } else {
        len = 0;
        crc = 0xFFFFFFFF;
        while (1) {
            if ((byte = str[len++]) == 0) break;
            crc = crc ^ byte;
            for (j = 0; j < 8; j++) {
                if ((crc & 1) != 0) {
                    crc = (crc >> 1) ^ 0xEDB88320;
                } else {
                    crc >>= 1;
                }
            }
        }
        crc ^= 0xFFFFFFFF;
        hash = (char *)malloc(9);
        if (hash != NULL) sprintf(hash, "%08X", crc);
    }
    return hash;
}