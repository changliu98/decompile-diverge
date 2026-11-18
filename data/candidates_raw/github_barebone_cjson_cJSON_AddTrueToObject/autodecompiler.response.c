cJSON * cJSON_AddTrueToObject(cJSON *object, const char *string)
{
    cJSON *boolean = cJSON_CreateTrue();
    cJSON_bool added_item;
    if (added_item = add_item_to_object(object, string, boolean, &global_hooks, ((cJSON_bool)0)))
    {
        return boolean;
    }
    else
    {
        cJSON_Delete(boolean);
        return NULL;
    }
}