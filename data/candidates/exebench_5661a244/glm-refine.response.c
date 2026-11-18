size_t __cdecl FAT_parse_directory(const char *directory, size_t dirlen, size_t *startpos, size_t *endpos)
{
    size_t start = *startpos;

    // Skip characters until we find a backslash or reach the end of the string
    while (start < dirlen && directory[start] != FAT_PATH_SEPARATOR)
        ++start;

    // If we reached the end without finding a separator, there are no more components
    if (start == dirlen)
    {
        *startpos = start;
        return 0;
    }

    // Move past the separator to point to the start of the current component
    ++start;
    *startpos = start;

    // Find the end of the current component (the next separator or end of string)
    size_t end = start + 1;
    while (end < dirlen && directory[end] != FAT_PATH_SEPARATOR)
        ++end;

    *endpos = end;
    return end - start;
}