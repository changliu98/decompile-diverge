int load_terminfo() {
    struct terminfo *ti;
    char buf[0x1000];
    int status = -1;
    int ret;
    FILE *fp;
    char *tok;

    // Attempt to load from environment variable (e.g. "TERMINFO")
    ti = getenv_terminfo("TERMINFO");
    if (ti == NULL) {
        return -1;
    }

    // Attempt to load from another environment variable (e.g. "TERM")
    const char *term_env = getenv_terminfo("TERM");
    if (term_env != NULL) {
        ret = load_terminfo_from_env(ti, term_env);
        if (ret == 0) {
            return ret;
        }
    }

    // Attempt to load from a specific path (e.g. "/usr/share/terminfo")
    fp = open_terminfo_path("/usr/share/terminfo");
    if (fp != NULL) {
        ret = snprintf_terminfo_path(buf, 0x1000, "%s", fp);
        if (ret < 0 || ret >= 0x1000) {
            return -1;
        }
        ret = load_terminfo_from_file(ti, buf);
        if (ret == 0) {
            return ret;
        }
    }

    // Attempt to load from a colon-separated list of paths (e.g. "TERMPATH")
    const char *term_path = getenv_terminfo("TERMPATH");
    if (term_path != NULL) {
        tok = strtok_terminfo((char *)term_path, ":");
        while (tok != NULL) {
            if (tok[0] != '\0') {
                ret = load_terminfo_from_string(ti, tok);
                if (ret == 0) {
                    return ret;
                }
            }
            tok = strtok_terminfo(NULL, ":");
        }
    }

    // Fallback to parsing individual terminal capabilities
    // If any of these fail, it falls through to the next one
    if (parse_terminfo_cap(ti, "cap1") == 0) return 0;
    if (parse_terminfo_cap(ti, "cap2") == 0) return 0;
    if (parse_terminfo_cap(ti, "cap3") == 0) return 0;
    if (parse_terminfo_cap(ti, "cap4") == 0) return 0;
    if (parse_terminfo_cap(ti, "cap5") == 0) return 0;
    if (parse_terminfo_cap(ti, "cap6") == 0) return 0;
    if (parse_terminfo_cap(ti, "cap7") == 0) return 0;
    if (parse_terminfo_cap(ti, "cap8") == 0) return 0;

    // If all attempts fail, return -1
    return -1;
}