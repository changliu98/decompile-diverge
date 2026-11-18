size_t func0(const char **strings, size_t count, const char *prefix, const char ***out)
{
    size_t prefix_length = strlen(prefix);
    size_t out_count = 0;

    *out = (const char **)malloc(count * sizeof(const char *));

    for (size_t i = 0; i < count; ++i)
    {
        if (strncmp(strings[i], prefix, prefix_length) == 0)
        {
            (*out)[out_count] = strings[i];
            out_count++;
        }
    }

    return out_count;
}