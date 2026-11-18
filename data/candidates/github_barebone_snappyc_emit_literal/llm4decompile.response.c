char *emit_literal(char *dest, const char *src, int len, _Bool allow_fast_path)
{
    int i;
    int count;
    char *p;

    len--;
    if (len < 60) {
        *dest++ = (char)(len << 2);
        if (allow_fast_path && len <= 16) {
            unaligned_copy64(src, dest);
            unaligned_copy64(src + 8, dest + 8);
            return dest + len;
        }
    } else {
        p = dest;
        dest++;
        for (count = 0; len > 0; count++) {
            *dest++ = (char)len;
            len >>= 8;
        }
        do { if (!(!(count >= 1))) { __assert_fail("!(!(count >= 1))", "func.c", 583, "char *emit_literal(char *, const char *, int, _Bool)"); } } while (0);
        do { if (!(!(count <= 4))) { __assert_fail("!(!(count <= 4))", "func.c", 584, "char *emit_literal(char *, const char *, int, _Bool)"); } } while (0);
        *p = (char)((count + 11) << 2);
    }
    memcpy(dest, src, (size_t)(len + 1));
    return dest + len;
}