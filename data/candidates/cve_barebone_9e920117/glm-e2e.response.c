int njs_module_path(void *vm, njs_str_s *dir, njs_module_s *m) {
    size_t size = 0;
    size_t dir_len = m->name_len;
    char path[4096];
    char *p;

    if (dir != NULL) {
        dir_len = dir->len;
        if (dir_len == 0) {
            return -3;
        }
        if (dir->data[dir_len - 1] != '/') {
            size = 1;
        }
        if (size != 0) {
            dir_len++;
        }
    }

    if (dir_len > 4096) {
        return -1;
    }

    p = path;
    if (dir != NULL) {
        memcpy(p, dir->data, dir->len);
        p += dir->len;
        if (size != 0) {
            *p++ = '/';
        }
    }

    memcpy(p, m->name, m->name_len);
    p += m->name_len;
    *p = '\0';

    if (realpath(path, m->path_buf) == NULL) {
        return -3;
    }

    m->fd = open(m->path_buf, O_RDONLY);
    if (m->fd < 0) {
        return -3;
    }

    m->path = m->path_buf;
    m->path_len = strlen(m->path);

    return 0;
}