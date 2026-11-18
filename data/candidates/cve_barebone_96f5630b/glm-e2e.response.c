char* vips_utf8_strcasestr(const char *haystack, const char *needle, int haystack_len) {
    long needle_char_len = g_utf8_strlen(needle, -1);
    int needle_byte_len = strlen(needle);
    const char *p = haystack;

    while (p - haystack <= (long)(haystack_len - needle_byte_len)) {
        const char *h_ptr = p;
        const char *n_ptr = needle;
        int i = 0;

        while (i < needle_char_len) {
            gunichar h_char = g_utf8_get_char_validated(h_ptr, haystack_len - (p - haystack));
            gunichar n_char = g_utf8_get_char_validated(n_ptr, -1);

            if (h_char == (gunichar)-1 || h_char == (gunichar)-2 ||
                n_char == (gunichar)-1 || n_char == (gunichar)-2) {
                return NULL;
            }

            if (h_char == 0) {
                return NULL;
            }

            if (g_unichar_tolower(h_char) != g_unichar_tolower(n_char)) {
                break;
            }

            h_ptr = g_utf8_find_next_char(h_ptr, haystack + haystack_len);
            n_ptr = g_utf8_find_next_char(n_ptr, NULL);
            i++;
        }

        if (i == needle_char_len) {
            return (char *)p;
        }

        p = g_utf8_find_next_char(p, NULL);
    }

    return NULL;
}