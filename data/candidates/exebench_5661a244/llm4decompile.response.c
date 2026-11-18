size_t FAT_parse_directory(const char *directory, size_t dirlen, size_t *startpos, size_t *endpos)
{
    size_t dirnamelen;

    while (*startpos < dirlen && directory[*startpos] != '\\')
        (*startpos)++;

    if (*startpos == dirlen)
        return 0;

    (*startpos)++;
    *endpos = *startpos + 1;

    while (*endpos < dirlen && directory[*endpos] != '\\')
        (*endpos)++;

    dirnamelen = *endpos - *startpos;

    return dirnamelen;
}