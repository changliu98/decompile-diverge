static void func0(char *p, int is_local) {
    if (is_local) {
        while (*p) {
            if (*p == '\0' || strchr(",.+-*/%=!;:~()<>[]?/\\", *p)) {
                *p = 'N';
            }
            p++;
        }
    } else {
        while (*p) {
            if (*p == '\0' || strchr(",.+-*/%=!;:~()<>[]?/\\", *p)) {
                *p = 'N';
            }
            p++;
        }
    }
}