cJSON * cJSON_CreateStringReference(const char *string)
{
    cJSON *reference = cJSON_New_Item(&global_hooks);
    if (reference == NULL)
    {
        return NULL;
    }
    reference->type = (1 << 7);
    reference->valuestring = (char*)cJSON_strdup((const unsigned char*)string, &global_hooks);
    if (reference->valuestring == NULL)
    {
        cJSON_Delete(reference);
        return NULL;
    }
    return reference;
}