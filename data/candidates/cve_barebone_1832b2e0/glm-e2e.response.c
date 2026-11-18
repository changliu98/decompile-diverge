int xrdp_wm_parse_domain_information(const char *str, int max_len, int flag, char *domain) {
    int rv = 0;
    char hex[2];
    int pos;
    int val;

    memset(domain, 0, 256);

    if (str[0] == '_') {
        pos = g_pos(str + 1, "\\");
        if (pos > 0) {
            if (flag != 0) {
                memset(hex, 0, 2);
                g_strncpy(hex, str + pos + 3, 1);
                val = g_htoi(hex);
                if (val > 0 && val < max_len) {
                    rv = val;
                }
            }
            g_strncpy(domain, str + 1, pos);
        } else {
            g_strncpy(domain, str + 1, 255);
        }
    }

    return rv;
}