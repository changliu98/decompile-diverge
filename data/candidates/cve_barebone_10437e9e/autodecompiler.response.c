char *bit_utf8_to_TU(char *utf8, int escapeQuotes)
{
    size_t i, j, len;
    unsigned short *wide;
    char *ret;

    j = 0;
    len = strlen(utf8);
    if(len >= 0xFFFF) {
        loglevel = 1; logprintf("U_Utf8ToWide: string length %d is too long for wide string conversion\n", len);
        len = 0xFFFF -1;
    }
    wide = calloc(2, len+1);
    if(!wide) {
        loglevel = 1; logprintf("U_Utf8ToWide: out of memory\n");
        ret = NULL;
        goto u_utf8towide_exit;
    }

    for(i=0; i<len; i++) {
        unsigned char c = utf8[i];
        if(c < 0x80) {
            if(escapeQuotes && c == '\\' && len > 1) {
                c = utf8[i++];
                switch(c) {
                    case 'n':
                        wide[j++] = '\n';
                        break;
                    case 'r':
                        wide[j++] = '\r';
                        break;
                    default:
                        wide[j++] = c;
                        break;
                }
            } else {
                wide[j++] = c;
            }
        } else if((c & 0xE0) == 0xC0) {
            if(len > 1) {
                wide[j++] = ((c & 0x1F) << 6) | (utf8[i+1] & 0x3F);
            }
            len--;
            i++;
        } else if((c & 0xF0) == 0xE0) {
            if(len > 2 && (((unsigned char)utf8[i+1] < 0x80) || ((unsigned char)utf8[i+1] > 0xBF) ||
                           ((unsigned char)utf8[i+2] < 0x80) || ((unsigned char)utf8[i+2] > 0xBF))) {
                continue;
            }
            if(len > 1 && ((c == 0xE0) && ((unsigned char)utf8[i+1] < 0xA0))) {
                continue;
            }
            if(len > 2) {
                wide[j++] = ((c & 0x0F) << 12) | ((utf8[i+1] & 0x3F) << 6) | (utf8[i+2] & 0x3F);
            }
            i++;
            i++;
            len--;
            len--;
        } else {

        }
    }
    wide[j] = 0;
    ret = (char *)wide;

u_utf8towide_exit:
    return(ret);
}