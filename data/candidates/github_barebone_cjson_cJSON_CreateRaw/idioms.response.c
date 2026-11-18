struct cJSON *cJSON_CreateRaw(char *raw)
{
    struct cJSON *item = cJSON_New_Item(&global_hooks);
    if (item == ((void *)0))
        return item;
    item->type = cJSON_Raw;
    item->valuestring = cJSON_strdup(raw,&global_hooks);
    if (item->valuestring == ((void *)0))
    {
        cJSON_Delete(item);
        return ((void *)0);
    }
    return item;
}