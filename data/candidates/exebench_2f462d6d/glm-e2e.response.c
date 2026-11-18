int putdword(char *ptr, int value) {
    ptr[0] = (char)value;
    ptr[1] = (char)(value >> 8);
    return value;
}