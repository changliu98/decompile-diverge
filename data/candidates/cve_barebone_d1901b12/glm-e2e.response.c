int do_bid_note(void *arg, const char *buf, int type, int namesz, int descsz, int align) {
    if (namesz == 4 && strcmp(buf + 16, "GNU") == 0 && type == 3) {
        if (descsz >= 4 && descsz <= 20) {
            *(int *)arg |= 0x10;
            
            const char *os;
            switch (descsz) {
                case 8:  os = "Linux"; break;
                case 16: os = "Hurd"; break;
                case 20: os = "Solaris"; break;
                default: os = "Unknown"; break;
            }
            
            if (file_printf(arg, ", OS: %s", os) == -1) {
                return 1;
            }
            
            char tmp[32];
            memcpy(tmp, buf + 24, descsz);
            
            for (int i = 0; i < descsz; i++) {
                if (file_printf(arg, " %02x", (uint8_t)tmp[i]) == -1) {
                    return 1;
                }
            }
            return 1;
        }
    }
    return 0;
}