void listdir(unsigned int depth, int f, TLS_FD *tls_fd, char *name)
{
    PureFileInfo *dir, *s;
    char *names;

    if (depth >= max_ls_depth || matches >= max_ls_files)
        return;

    dir = sreaddir(&names);
    if (dir == NULL) {
        addreply(226, "Sorry, we were unable to read [%s]", name);
        return;
    }

    for (s = dir; s->name_offset != (off_t)-1; s++) {
        int d = 0;

        if (names[s->name_offset] != '.')
            d = listfile(s, NULL);
        else if (opt_a &&
                 (names[s->name_offset + 1] == '\0' ||
                  (names[s->name_offset + 1] == '.' &&
                   names[s->name_offset + 2] == '\0')))
            listfile(s, NULL);
        else if (opt_a)
            d = listfile(s, NULL);
        if (!d)
            s->name_offset = (off_t)-1;
    }
    outputfiles(f, tls_fd);

    for (s = dir; opt_R && s != dir; s++) {
        if (s->name_offset == (off_t)-1)
            continue;
        if (!chdir(names + s->name_offset)) {
            char subdir[4096 + 1];

            if (subdir == NULL)
                break;
            if (snprintf(subdir, sizeof(subdir), "%s/%s",
                         name, names + s->name_offset) >= (int)sizeof(subdir))
                break;
            wrstr(f, tls_fd, "\r\n\r\n");
            wrstr(f, tls_fd, subdir);
            wrstr(f, tls_fd, ":\r\n\r\n");
            listdir(depth + 1, f, tls_fd, subdir);
            if (matches >= max_ls_files)
                break;
            if (!chdir(".."))
                continue;
            if (!chdir(wd) || !chdir(name))
                continue;
            die(421, 3, "chdir: %s", strerror((*__errno_location ())));
        }
    }
    do { char *__ptr = (names); if ((__ptr) != NULL) { free((void *) __ptr); __ptr = NULL; } } while (0);
    do { char *__ptr = (dir); if ((__ptr) != NULL) { free((void *) __ptr); __ptr = NULL; } } while (0);
}