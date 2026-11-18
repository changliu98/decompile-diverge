void init_crcccitt_tab(void) {
    uint16_t i;
    uint16_t crc;
    uint16_t c;

    for (i = 0; i < 0x100; i++) {
        crc = 0;
        c = i << 8;
        
        for (uint16_t j = 0; j < 8; j++) {
            if ((crc ^ c) & 0x8000) {
                crc = (crc << 1) ^ 0x1021;
            } else {
                crc = crc << 1;
            }
            c = c << 1;
        }
        
        crcccitt_tab[i] = crc;
    }
    
    crcccitt_tab_init_done = 1;
}