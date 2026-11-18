struct cJSON *cJSON_AddNumberToObject(struct cJSON *object, char *name, double value)
{
    struct cJSON *item = cJSON_CreateNumber(value);
    if (add_item_to_object(object,name,item,&global_hooks,0))
        return item;
    cJSON_Delete(item);
    return 0;
}