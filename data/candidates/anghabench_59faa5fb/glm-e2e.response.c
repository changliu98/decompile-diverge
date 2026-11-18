void scsi_sanitize_inquiry_string(unsigned char *s, int len) {
    int all_zero = 0;
    
    while (len > 0) {
        if (*s == 0) {
            all_zero = 1;
        }
        
        if (!all_zero) {
            if (*s < 0x20 || *s > 0x7e) {
                *s = 0x20;
            }
        }
        
        len--;
        s++;
    }
}