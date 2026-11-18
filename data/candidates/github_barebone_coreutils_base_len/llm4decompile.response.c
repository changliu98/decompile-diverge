size_t base_len(const char *name)
{
    size_t len = strlen(name);
    while (len > 1 && name[len - 1] == '/')
        --len;
    return len;
}