cJSON *cJSON_ParseWithOpts(const char *buffer, const char **return_parse_end, int require_null_terminated)
{
    size_t length = 0;
    cJSON *c;

    if (buffer == NULL)
    {
        return NULL;
    }

    length = strlen(buffer) + 1;
    c = cJSON_ParseWithLengthOpts(buffer, length, return_parse_end, require_null_terminated);
    if (c == NULL)
    {
        return NULL;
    }

    return c;
}