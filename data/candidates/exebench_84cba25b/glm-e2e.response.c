char* base91(char* str, int val) {
    *str++ = (char)((val / 91) + 0x21);
    *str++ = (char)((val % 91) + 0x21);
    return str;
}