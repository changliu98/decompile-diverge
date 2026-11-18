void listdir(int depth, int fd, void *stream, const char *dir) {
    struct dirinfo *dirp;
    struct dirinfo *entry;
    struct dirinfo *entry2;
    char *path;
    int ret;

    if (depth >= max_ls_depth || matches >= max_ls_files) {
        return;
    }

    dirp = sreaddir(&dir);
    if (dirp == NULL) {
        addreply(226, "Can't open directory %s.", dir);
        return;
    }

    entry = dirp;
    while (entry->offset != -1) {
        ret = 0;
        if (entry->name[0] == '.') {
            if (opt_a) {
                if (entry->name[1] == '\0' || (entry->name[1] == '.' && entry->name[2] == '\0')) {
                    listfile(entry, 0);
                } else {
                    ret = listfile(entry, 0);
                }
            }
        } else {
            ret = listfile(entry, 0);
        }
        if (ret == 0) {
            entry->offset = -1;
        }
        entry = (struct dirinfo *)((char *)entry + 0x38);
    }

    outputfiles(fd, stream);

    entry2 = dirp;
    int do_recurse = 0;
    do {
        if (opt_R && entry2 != entry) {
            if (entry2->offset != -1) {
                if (chdir(entry2->name) == 0) {
                    path = alloca(0x1001);
                    if (path != NULL) {
                        if (snprintf(path, 0x1001, "%s/%s", entry2->name, dir) < 0x1001) {
                            wrstr(fd, stream, "\n");
                            wrstr(fd, stream, path);
                            wrstr(fd, stream, ":\n");
                            listdir(depth + 1, fd, stream, path);
                        }
                    }
                    if (matches >= max_ls_files) {
                        break;
                    }
                    if (chdir("..") != 0) {
                        if (chdir(wd) != 0) {
                            if (chdir(dir) != 0) {
                                die(421, 3, "Can't change directory to %s: %s.", dir, strerror(errno));
                            }
                        }
                    }
                }
            }
            entry2 = (struct dirinfo *)((char *)entry2 + 0x38);
        }
    } while (opt_R && entry2 != entry);

    free(dir);
    free(dirp);
    dir = NULL;
}