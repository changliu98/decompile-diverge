int enddata(char *arg1, int arg2) {
    int remainder = arg2 & 0x3f;
    int quotient = arg2 - remainder;
    int result;

    if (remainder == 0) {
        result = 0;
    } else {
        arg1[quotient + 1] = (char)(remainder - 1);
        result = quotient + 0x40;
    }

    return result;
}