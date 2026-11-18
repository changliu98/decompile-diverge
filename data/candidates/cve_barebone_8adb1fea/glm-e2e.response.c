void ga_concat_shorten_esc(void *ga, char *str) {
    char buf[0x60]; // -0x70 to -0x10 (size 96, but likely 64 for string + padding)
    int c;
    int len;
    int same_chars;
    char *p;
    char *s;

    if (str == NULL) {
        ga_concat(ga, "...");
        return;
    }

    s = str;
    while (*s != '\0') {
        same_chars = 1;
        p = s;
        c = mb_ptr2char_adv(&p);
        len = p - s;

        while (*p != '\0' && c == mb_ptr2char(p)) {
            same_chars++;
            p += len;
        }

        if (same_chars > 20) {
            ga_concat(ga, "[");
            ga_concat_esc(ga, s, len);
            ga_concat(ga, "]");
            // Format string is likely "%d times", matching the 0x41 (65) buffer size
            vim_snprintf(buf, 65, "%d times", same_chars);
            ga_concat(ga, buf);
            ga_concat(ga, " ");
            s = p - 1;
        } else {
            ga_concat_esc(ga, s, len);
        }
        s++;
    }
}