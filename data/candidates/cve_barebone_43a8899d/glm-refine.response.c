cJSON * __cdecl get_object_item(const cJSON *const object, const char *const name, const cJSON_bool case_sensitive)
{
    cJSON *current_element;

    if (!object || !name)
        return NULL;

    current_element = object->child;

    if (case_sensitive)
    {
        while (current_element && strcmp(name, current_element->string) != 0)
        {
            current_element = current_element->next;
        }
    }
    else
    {
        while (current_element && case_insensitive_strcmp((const unsigned __int8 *)name, (const unsigned __int8 *)current_element->string) != 0)
        {
            current_element = current_element->next;
        }
    }

    return current_element;
}