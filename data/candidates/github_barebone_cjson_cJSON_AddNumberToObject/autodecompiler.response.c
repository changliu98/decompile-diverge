cJSON * cJSON_AddNumberToObject(cJSON *object, const char *string, double number)
{
    cJSON *number_item = cJSON_CreateNumber(number);
    cJSON *return_item;
    if (add_item_to_object(object, string, number_item, &global_hooks, ((cJSON_bool)0)))
    {
        return_item = number_item;
    }
    else
    {
        cJSON_Delete(number_item);
        return_item = NULL;
    }

    return return_item;
}