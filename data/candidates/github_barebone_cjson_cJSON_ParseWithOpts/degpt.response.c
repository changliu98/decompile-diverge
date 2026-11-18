cJSON * cJSON_ParseWithOpts(char *json_string, char **parse_end_ptr, cJSON_bool require_null_terminated)
{
    if (json_string == NULL) {
        return NULL;
    }
    return cJSON_ParseWithLengthOpts(json_string, strlen(json_string) + 1, parse_end_ptr, require_null_terminated);
}