size_t FAT_parse_directory(const char *directory, size_t dirlen, size_t *startpos, size_t *endpos)
{
    while (*startpos < dirlen)
    {
        if (directory[*startpos] == '\\')
            break;
        (*startpos)++;
    }

    if (*startpos == dirlen)
        return 0;

    *startpos += 1;
    *endpos = *startpos + 1;
    while (*endpos < dirlen)
    {
        if (directory[*endpos] == '\\')
            break;
        (*endpos)++;
    }
    return (*endpos - *startpos);
}