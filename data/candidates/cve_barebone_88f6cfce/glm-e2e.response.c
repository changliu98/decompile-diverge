void append_command(char *cmd) {
    char *p = cmd;
    char *IObuff_end = IObuff + strlen(IObuff);
    
    while (*p != '\0' && IObuff_end - IObuff < 0x3fa) {
        if (enc_utf8) {
            if ((unsigned char)*p == 0xc2 && (unsigned char)*(p + 1) == 0xa0) {
                p += (enc_utf8 ? 2 : 1);
                strcpy(IObuff_end, "    ");
                IObuff_end += 4;
                continue;
            }
        } else {
            if ((unsigned char)*p == 0xa0) {
                p += (enc_utf8 ? 2 : 1);
                strcpy(IObuff_end, "    ");
                IObuff_end += 4;
                continue;
            }
        }
        
        if (has_mbyte) {
            mb_copy_char(&p, &IObuff_end);
        } else {
            *IObuff_end++ = *p++;
        }
    }
    
    *IObuff_end = '\0';
}