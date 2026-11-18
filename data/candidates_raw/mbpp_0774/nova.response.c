static const char *func0(const char *name) {
    const char *p;
    char buf[9];
    if (strncmp(buf, name, 9) == 0) {
        p = "YES";
    } else {
        int rc = sscanf(name, "%8[^0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ]"
                            "%08X%08X%08X%08X%08X%08X%08X%08X",
                        buf, &A, &B, &C, &D, &E, &F, &G);
        assert(rc);
        if (rc == 0) {
            p = "NO";
        } else {
            p = "YES";
        }
    }
    return p;
}