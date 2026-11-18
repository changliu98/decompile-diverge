cJSON *cJSON_CreateDoubleArray(const double *numbers, int count) {
    cJSON *ret = NULL;
    cJSON *array = NULL;
    cJSON *item = NULL;
    cJSON *prev = NULL;
    int i = 0;

    if (count < 0 || numbers == NULL) {
        return NULL;
    }

    array = cJSON_CreateArray();
    
    while (array != NULL && i < count) {
        item = cJSON_CreateNumber(numbers[i]);
        
        if (item == NULL) {
            cJSON_Delete(array);
            return NULL;
        }
        
        if (i == 0) {
            array->child = item;
        } else {
            suffix_object(prev, item);
        }
        
        prev = item;
        i++;
    }
    
    if (array != NULL && array->child != NULL) {
        array->child->prev = item;
    }
    
    ret = array;
    return ret;
}