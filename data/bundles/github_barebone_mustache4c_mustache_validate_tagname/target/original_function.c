static int
mustache_validate_tagname(const char* tagname, size_t size)
{
    off_t off;

    if(size == 1  &&  tagname[0] == '.')
        return 0;

    /* Verify there is no whitespace and that '.' is used only as a delimiter
     * of non-empty tokens. */
    if(tagname[0] == '.'  ||  tagname[size-1] == '.')
        return -1;
    for(off = 0; off < size; off++) {
        if(MUSTACHE_ISWHITESPACE(tagname[off]))
            return -1;
        if(tagname[off] == '.'  &&  off+1 < size  &&  tagname[off+1] == '.')
            return -1;
    }

    return 0;
}