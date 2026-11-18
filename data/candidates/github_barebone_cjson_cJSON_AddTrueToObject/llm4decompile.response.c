cJSON * cJSON_AddTrueToObject(cJSON *object, const char *name)
{
    cJSON *item = cJSON_CreateTrue();
    if(add_item_to_object(object, name, item, &global_hooks, NULL))
    {
        return item;
    }
    else
    {
        cJSON_Delete(item);
        return NULL;
    }
}