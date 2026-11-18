cJSON * cJSON_AddNumberToObject(cJSON *object, const char *string, double number)
{
    cJSON *item = cJSON_CreateNumber(number);
    if(add_item_to_object(object, string, item, &global_hooks, NULL))
    {
        return item;
    }
    else
    {
        cJSON_Delete(item);
        return NULL;
    }
}