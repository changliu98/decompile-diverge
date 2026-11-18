char *__cdecl checkpath(char *path, const char *srcpath)
{
    char *p = path;

    if (path && srcpath)
    {
        while (*srcpath)
        {
            if (*srcpath == '\\')
            {
                *p++ = '/';
                ++srcpath;
            }
            else
            {
                *p++ = *srcpath++;
            }
        }
        *p = *srcpath; // Equivalent to *p = '\0'
    }
    return path;
}