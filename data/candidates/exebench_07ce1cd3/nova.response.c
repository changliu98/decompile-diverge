int file_perms_get(char *filename, int *lineno, int *col) {
    struct stat st;

    if (*lineno)
        *lineno = 0;
    if (*col)
        *col = 0;

    if (stat(filename, &st) < 0)
        return -1;

    if (lineno)
        *lineno = st.st_size;
    if (col)
        *col = st.st_mode & 0777;

    return 0;
}