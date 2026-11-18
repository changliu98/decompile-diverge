cJSON * cJSON_AddRaw(cJSON *object, const char *string, const char *raw)
{
    cJSON *raw_item = cJSON_CreateRaw(raw);
    cJSON *return_value;
    if (!add_item_to_object(object, string, raw_item, &global_hooks, ((cJSON_bool)0)))
    {
        cJSON_Delete(raw_item);
        return_value = NULL;
    }
    else
    {
        return_value = raw_item;
    }

    return return_value;
}