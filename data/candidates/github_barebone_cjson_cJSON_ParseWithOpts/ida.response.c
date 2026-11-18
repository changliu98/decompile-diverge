cJSON *__cdecl cJSON_ParseWithOpts(
        const char *value,
        const char **return_parse_end,
        cJSON_bool require_null_terminated)
{
  size_t buffer_length; // [rsp+8h] [rbp-28h]

  if ( !value )
    return 0LL;
  buffer_length = strlen(value) + 1;
  return cJSON_ParseWithLengthOpts(value, buffer_length, return_parse_end, require_null_terminated);
}