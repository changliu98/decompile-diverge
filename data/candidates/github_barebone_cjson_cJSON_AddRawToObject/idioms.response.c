static struct cJSON *cJSON_AddRawToObject(struct cJSON *object, char *name, char *raw)
{
    struct cJSON *item = cJSON_CreateRaw(raw);
    if (add_item_to_object(object, name, item, &global_hooks, 0))
        return item;
    cJSON_Delete(item);
    return 0;
}