void check_long(long a, long b, char *out) {
    *out = (b - a == 8) ? 0x74 : 0x66;
}