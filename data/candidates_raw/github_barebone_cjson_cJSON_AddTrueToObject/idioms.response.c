static struct cJSON *cJSON_AddTrueToObject(struct cJSON *const object, char *const name)
{
    struct cJSON *item = cJSON_CreateTrue();
    if (add_item_to_object(object, name, item, &global_hooks, 0))
        return item;
    cJSON_Delete(item);
    return ((void *)0);
}