char* cJSON_SetValuestring(cJSON *object, const char *valuestring)
{
    char *new_string = NULL;
    size_t new_string_length = 0;
    size_t old_string_length = 0;

    if ((object == NULL) || ((object->type & 16) == 0) || ((object->type & 256) != 0))
    {
        return NULL;
    }

    if (object->valuestring == NULL)
    {
        return NULL;
    }

    if (valuestring == NULL)
    {
        return NULL;
    }

    new_string_length = strlen(valuestring);
    old_string_length = strlen(object->valuestring);

    if (new_string_length <= old_string_length)
    {
        if ((valuestring >= object->valuestring) && ((valuestring + new_string_length) <= (object->valuestring + old_string_length)))
        {
            return NULL;
        }
        strcpy(object->valuestring, valuestring);
        return object->valuestring;
    }

    new_string = (char*)cJSON_strdup((const unsigned char*)valuestring, &global_hooks);
    if (new_string == NULL)
    {
        return NULL;
    }
    if (object->valuestring != NULL)
    {
        cJSON_free(object->valuestring);
    }
    object->valuestring = new_string;

    return new_string;
}