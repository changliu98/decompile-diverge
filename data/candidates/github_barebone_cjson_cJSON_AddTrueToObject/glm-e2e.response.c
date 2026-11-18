cJSON *cJSON_AddTrueToObject(cJSON *object, const char *name) {
    cJSON *true_item = cJSON_CreateTrue();
    cJSON *ret = NULL;

    if (add_item_to_object(object, name, true_item, false)) {
        ret = true_item;
    } else {
        cJSON_Delete(true_item);
        ret = NULL;
    }

    return ret;
}