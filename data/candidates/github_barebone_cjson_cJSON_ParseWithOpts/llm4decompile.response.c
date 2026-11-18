cJSON *cJSON_ParseWithOpts(const char *value, const char **return_parse_end, cJSON_bool require_null_terminated)
{
    return value ? cJSON_ParseWithLengthOpts(value, (size_t)strlen(value) + sizeof(""), return_parse_end, require_null_terminated) : NULL;
}