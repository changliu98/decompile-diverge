char *checkpath(char *path, const char *srcpath)
{
    char *p;

    if (path == NULL || srcpath == NULL)
        return path;

    p = path;
    while (*srcpath != 0)
    {
        if (*srcpath == '\\')
            *p++ = '/';
        else
            *p++ = *srcpath;

        srcpath++;
    }

    *p = *srcpath;

    return path;
}