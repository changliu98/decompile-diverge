void* cJSON_ParseWithOpts(const char *value, void *return_parse_end, int require_null_terminated) {
    void *cjson = NULL;

    if (value != NULL) {
        size_t buffer_length = strlen(value) + 1;
        cjson = cJSON_ParseWithLengthOpts(value, buffer_length, return_parse_end, require_null_terminated);
    }
    
    return cjson;
}