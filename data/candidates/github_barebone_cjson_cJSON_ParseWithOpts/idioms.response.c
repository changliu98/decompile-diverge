struct cJSON *cJSON_ParseWithOpts(char *value, char **return_parse_end, enum cJSON_bool require_null_terminated)
{
    if ( !value )
        return ((void *)0);
    return cJSON_ParseWithLengthOpts( value, strlen(value)+1, return_parse_end, require_null_terminated );
}