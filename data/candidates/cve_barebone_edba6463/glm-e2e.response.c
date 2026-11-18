void process_COM(const unsigned char *data, int length) {
    char buffer[0x3E80];
    int buf_idx = 0;

    if (length > 0x3E80) {
        length = 0x3E80;
    }

    for (int i = 2; i < length; i++) {
        unsigned char c = data[i];
        
        if (c == 0x0D && data[i + 1] == 0x0A) {
            i++; // Skip the next character (0x0A)
            continue;
        }
        
        if (c >= 0x20 || c == 0x0A || c == 0x09) {
            buffer[buf_idx++] = c;
        } else {
            buffer[buf_idx++] = '?';
        }
    }
    
    buffer[buf_idx] = '\0';
    
    if (ShowTags != 0) {
        printf("Comment: %s\n", buffer);
    }
    
    strcpy(ImageInfo, buffer);
}