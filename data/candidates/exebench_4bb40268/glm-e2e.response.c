void check_int(int a, int b, char *out) {
    *out = (b - a == 4) ? 0x74 : 0x66;
}