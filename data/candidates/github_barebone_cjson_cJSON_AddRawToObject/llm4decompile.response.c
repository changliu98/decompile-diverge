cJSON *cJSON_AddRawToObject(cJSON *object, const char *name, char *raw)
{
    cJSON *item = cJSON_CreateRaw(raw);
    if (add_item_to_object(object, name, item, &global_hooks, NULL))
    {
        return item;
    }
    cJSON_Delete(item);
    return NULL;
}