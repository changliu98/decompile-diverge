static void listdir(int fd, int flags, const char *path, const char *name) {
    struct stat st;
    struct dirent *de;
    DIR *dir;
    char *buf;
    int i;

    while (1) {
        if (fd >= SOPEN_MAX || fd >= sysconf(_SC_OPEN_MAX)) {
            errno = EBADF;
            goto err;
        }
        if (fstat(fd, &st)!= 0) {
            errno = EBADF;
            goto err;
        }
        if (S_ISDIR(st.st_mode)) {
            dir = fdopendir(fd);
            if (dir == NULL) {
                errno = EBADF;
                goto err;
            }
            while ((de = readdir(dir))!= NULL) {
                if (strcmp(de->d_name, ".") == 0 ||
                    strcmp(de->d_name, "..") == 0)
                    continue;
                i = stat(de->d_name, &st);
                if (i!= 0) {
                    errno = EBADF;
                    goto err;
                }
                if (S_ISDIR(st.st_mode)) {
                    buf = (char *)alloca(sizeof(char) * (strlen(path) + strlen(name) + 1));
                    sprintf(buf, "%s/%s", path, name);
                    listdir(fd + 1, flags, buf, name);
                }
            }
            closedir(dir);
            dir = NULL;
        }
    }
err:
    if (dir!= NULL)
        closedir(dir);
    dir = NULL;
}