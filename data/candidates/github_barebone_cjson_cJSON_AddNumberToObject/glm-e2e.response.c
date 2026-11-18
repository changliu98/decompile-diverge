cJSON *cJSON_AddNumberToObject(cJSON *object, const char *name, double number) {
    cJSON *new_item;
    cJSON *ret;

    new_item = cJSON_CreateNumber(number);
    
    if (add_item_to_object(object, name, new_item, (const void *)0xb0c0, 0)) {
        ret = new_item;
    } else {
        cJSON_Delete(new_item);
        ret = NULL;
    }

    return ret;
}