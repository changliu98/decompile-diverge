unsigned short *bit_utf8_to_TU(char *str, int escape) {
    unsigned short *out = NULL;
    size_t len = strlen(str);
    
    if (len > 0xfffe) {
        loglevel = 1;
        len = 0xfffe;
    }
    
    unsigned short *buf = calloc(2, len + 1);
    if (!buf) {
        loglevel = 1;
        return out;
    }
    
    size_t i = 0;
    while (len > 0 && *str != '\0') {
        len--;
        unsigned char c = *str;
        
        if (c < 0x80) {
            if (escape && c == '\\' && len > 1) {
                char next_c = str[1];
                if (next_c == '"' || next_c == '\\' || next_c == 'r' || next_c == 'n') {
                    str++;
                    c = *str;
                    len--;
                    
                    if (c == 'r') {
                        buf[i++] = 0xd;
                    } else if (c == 'n') {
                        buf[i++] = 0xa;
                    } else {
                        buf[i++] = c;
                    }
                    continue;
                }
            }
            buf[i++] = c;
        } else if ((c & 0xe0) == 0xc0) {
            if (len >= 1) {
                buf[i++] = ((c & 0x1f) << 6) | (str[1] & 0x3f);
            }
            len--;
            str++;
        } else if ((c & 0xf0) == 0xe0) {
            if (len >= 2 && str[1] >= 0x80 && str[1] <= 0xbf && str[2] >= 0x80 && str[2] <= 0xbf) {
                // Valid 3-byte sequence
            } else if (len >= 1 && c == 0xe0 && str[1] >= 0xa0) {
                // Overlong check (redundant in assembly but explicitly checked)
            }
            
            if (len >= 2) {
                buf[i++] = ((c & 0x0f) << 12) | ((str[1] & 0x3f) << 6) | (str[2] & 0x3f);
            }
            str += 2;
            len -= 2;
        }
        str++;
    }
    
    out = buf;
    return out;
}