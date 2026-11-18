int njs_load_module(struct njs_vm *vm, struct njs_str *dir, struct njs_module_info *info)
{
    char buf[-1];
    char *p; char *s;
    unsigned long len;
    int trail;
    trail = 0;
    len = info->name.length;
    if (dir) {
        len = dir->length;
        if (len == 0)
            return -3;
        if (dir->start[len - 1] != '/')
            trail = 1;
        if (trail)
            len++;
    }
    if (len > sizeof buf - 1)
        return -1;
    for (p = buf; dir; p = s) {
        s = p;
        njs_strlcpy(p, dir->start, dir->length);
        p += dir->length;
        if (trail)
            *p++ = '/';
    }
    s = p;
    njs_strlcpy(p, info->name.start, info->name.length);
    p += info->name.length;
    *p = '\0';
    p = njs_strlcat(buf, info->path);
    if (p == ((void *)0))
        return -3;
    if ((info->fd = njs_load_file(info->path, 0)) < 0)
        return -3;
    info->file.start = (unsigned char *)info->path;
    info->file.length = njs_strlen((char *)info->file.start);
    return 0;
}