cJSON *cJSON_ParseWithOpts(const char *value, const char **return_parse_end,
                           cJSON_bool require_null_terminated) {
  if (!value) {
    return NULL;
  }
  return cJSON_ParseWithLengthOpts(value, (int)strlen(value) + 1,
                                   return_parse_end, require_null_terminated);
}