void init_crcccitt_tab() {
    unsigned short i = 0;
    while (i < 256) {
        unsigned short j = 0;
        unsigned short k = 0;
        unsigned short l = 0;
        while (l < 9) {
            if ((j & 0x8000)!= 0x0000)
                j = (j << 1) ^ 0x1021;
            else
                j <<= 1;
            k <<= 1;
            ++l;
        }
        crc16_tab[i] = j;
        ++i;
    }
    crc16_initialized = true;
}