char * cJSON_SetValuestring( cJSON *object, const char *value )
{
    char *copy = NULL;
    size_t value_length = 0;
    size_t old_string_length;

    if ((object == NULL) || !(object->type & 16) || (object->type & 256))
    {
        return NULL;
    }

    if (!(object->valuestring))
    {
        if (value == NULL)
        {
            return NULL;
        }
        else
        {
            return NULL;
        }
    }

    value_length = strlen(value);

    if (value_length <= strlen(object->valuestring))
    {

        if (value + value_length >= object->valuestring && value <= object->valuestring + old_string_length)
        {
            return NULL;
        }

        strcpy(object->valuestring, value);
        return object->valuestring;
    }

    copy = (char*) cJSON_strdup((const unsigned char*)value, &global_hooks);
    if (copy == NULL)
    {
        return NULL;
    }

    if (object->valuestring != NULL)
    {
        cJSON_free(object->valuestring);
    }
    object->valuestring = copy;

    return copy;
}