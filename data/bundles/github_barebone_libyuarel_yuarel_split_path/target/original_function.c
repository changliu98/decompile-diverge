int yuarel_split_path(char *path, char **parts, int max_parts)
{
    int i = 0;

    if (NULL == path || '\0' == *path)
    {
        return -1;
    }

    do
    {
        /* Forward to after slashes */
        while (*path == '/')
        {
            path++;
        }

        if ('\0' == *path)
        {
            break;
        }

        parts[i++] = path;

        path = strchr(path, '/');
        if (NULL == path)
        {
            break;
        }

        *(path++) = '\0';
    } while (i < max_parts);

    return i;
}