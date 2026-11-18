cJSON * cJSON_CreateString(const char *string)
{
    cJSON *reference = cJSON_New_Item(&global_hooks);
    if (reference == NULL)
    {
        return NULL;
    }

    reference->type = (1 << 4);

    reference->valuestring = (char*)cJSON_strdup((const unsigned char*)string, &global_hooks);
    if (reference->valuestring == NULL)
    {
        cJSON_Delete(reference);
        return NULL;
    }

    return reference;
}