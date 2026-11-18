int mobi_search_links_kf7(struct dirent *dp, DIR *dirp, unsigned long loc) {
    unsigned long size;
    unsigned long i;
    char *p;
    int ret;

    if (dp == NULL) {
        ret = 2;
    } else {
        dp->d_fileno = 0;
        dp->d_reclen = 0;
        dp->d_name[0] = '\0';
        if (dirp == NULL || loc == 0) {
            ret = 2;
        } else {
            do {
                size = strlen(dirname);
                p = dirp->buf + loc;
                if (p + size > dirp->buf + BUFSIZE) {
                    ret = 2;
                } else {
                    for (i = 0; i < size; i++) {
                        if (p[i]!= '/') {
                            break;
                        }
                    }
                    if (p[i] == '/') {
                        p += i + 1;
                        i = -i;
                    } else {
                        p = NULL;
                    }
                    dp->d_fileno = *(unsigned long *)p;
                    dp->d_reclen = 0;
                    ret = 0;
                }
            } while (ret == 0 && (p = find_next_entry(p, i))!= NULL);
            dp->d_reclen = p - dirp->buf;
            dp->d_name[0] = '\0';
            ret = 2;
        }
    }
    return ret;
}