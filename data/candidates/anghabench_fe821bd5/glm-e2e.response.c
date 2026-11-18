int ok_cp1251(char *str, int len) {
    for (int i = 1; i < len; i++) {
        // movsbl loads a signed byte and extends it to 32-bit int.
        // 0xffffff98 is the 32-bit two's complement representation of -104 (0x98)
        if ((int)str[i] == -104) {
            return 0;
        }
    }
    return 1;
}