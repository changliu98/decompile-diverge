void init_crctabccitt()
{
    unsigned short i, j;
    unsigned short c, c_tabccitt;

    for (i = 0; i < 256; i++) {

        c_tabccitt = 0;
        c = ((unsigned short) i) << 8;

        for (j = 0; j < 8; j++) {
            if ( (c_tabccitt ^ c) & 0x8000 ) c_tabccitt = ( c_tabccitt << 1 ) ^ 0x1021;
            else c_tabccitt <<= 1;
            c <<= 1;
        }
        crc_tabccitt[i] = c_tabccitt;
    }
    crc_tabccitt_init = 1;
}