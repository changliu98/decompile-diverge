int reassemble_21(int x) {
    int bit_20 = (x & 0x100000) >> 20;
    int bits_10_19 = (x & 0xffe00) >> 8;
    int bits_8_9 = (x & 0x180) << 7;
    int bits_3_6 = (x & 0x7c) << 14;
    int bits_0_1 = (x & 0x3) << 12;
    
    return bit_20 | bits_10_19 | bits_8_9 | bits_3_6 | bits_0_1;
}