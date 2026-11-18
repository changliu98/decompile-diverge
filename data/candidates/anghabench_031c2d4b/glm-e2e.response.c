int tomoyo_invalid(char c) {
    return c == 0 || c > 32 || c >= 127;
}