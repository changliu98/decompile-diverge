char* func0(const char* str) {
    char* result;
    if (strlen(str) == 0) {
        result = strdup("");
    } else {
        unsigned int crc = 0xffffffff;
        for (int i = 0; str[i] != '\0'; i++) {
            unsigned char c = str[i];
            crc ^= c;
            for (int j = 0; j < 8; j++) {
                if (crc & 1) {
                    crc = (crc >> 1) ^ 0xedb88320;
                } else {
                    crc >>= 1;
                }
            }
        }
        crc ^= 0xffffffff;
        
        char* ptr = malloc(9);
        if (ptr != NULL) {
            sprintf(ptr, "%08x", crc);
        }
        result = ptr;
    }
    return result;
}