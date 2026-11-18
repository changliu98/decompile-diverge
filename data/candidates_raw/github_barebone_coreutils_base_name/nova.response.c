char *func0(const char *path) {
    char *dir = strdup(path);
    char *base;
    int dirlen;

    
    if (*dir) {
        base = dir + (dirlen = strlen(dir)) - 1;
        base += (*base == '/')? 1 : 0;
    } else {
        base = dir;
        dirlen = 0;
    }

    
    base = zrealloc(base, dirlen + 1);
    if (dirlen) {
        base[0] = '.';
        base[1] = '/';
    }
    strncpy(base + dirlen, dir, dirlen);
    base[dirlen] = '\0';
    return base;
}