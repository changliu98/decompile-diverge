int writefile(char *path, struct stat *sb) {
    FILE *fd;
    int ret;

    if ((fd = fopen(path, "r")) == NULL) {
        sprintf(error, "Cannot open \"%s\"", path);
        return (ERROR);
    }

    ret = 0;
    if ((fstat(fileno(fd), sb))!= ERROR) {
        if (S_ISREG(sb->st_mode)) {
            if (fclose(fd)!= EOF) {
                sprintf(error, "Error closing file \"%s\"", path);
                ret = ERROR;
            }
        } else {
            sprintf(error, "\"%s\" is not a file", path);
            ret = ERROR;
        }
    } else {
        sprintf(error, "Cannot stat file \"%s\"", path);
        ret = ERROR;
    }

    return (ret);
}