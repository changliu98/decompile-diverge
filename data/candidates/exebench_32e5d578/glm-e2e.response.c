void intToBin(int num, int *binArray) {
    int mask = 0x80;
    for (int i = 0; i < 8; i++) {
        binArray[i] = (num & mask) != 0;
        num <<= 1;
    }
}