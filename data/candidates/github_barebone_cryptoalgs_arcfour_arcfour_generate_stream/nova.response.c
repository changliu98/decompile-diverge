void arcfour_generate_stream(unsigned char *buf, unsigned char *s, long long buf_len) {
    long long i = 0;
    int a = 0;
    int b = 0;
    while (i < buf_len) {
        a = (a + 1) % 256;
        b = (b + buf[a]) % 256;
        swap_char(buf, a, b);
        s[i] = buf[(buf[a] + buf[b]) % 256];
        i++;
    }
}