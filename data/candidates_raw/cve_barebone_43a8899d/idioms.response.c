struct cJSON *get_object_item(struct cJSON *object, char *name, enum cJSON_bool case_sensitive)
{
    if (object == ((void *)0) || name == ((void *)0))
        return ((void *)0);
    struct cJSON *current_element = object->child;
    if (case_sensitive)
    {
        for (; !(!strcmp(name, current_element->string)); current_element = current_element->next)
        {
            if (current_element == ((void *)0))
                break;
        }
    }
    else
    {
        for (; !(!case_insensitive_strcmp((unsigned char *)name, (unsigned char *)current_element->string)); current_element = current_element->next)
        {
            if (current_element == ((void *)0))
                break;
        }
    }
    return current_element;
}