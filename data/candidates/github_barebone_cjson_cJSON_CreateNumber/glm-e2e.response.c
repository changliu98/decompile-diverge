cJSON *cJSON_CreateNumber(double num) {
    cJSON *item = cJSON_New_Item();
    if (item != NULL) {
        item->type = 8; // Assuming 8 represents a Number type in cJSON
        item->valuedouble = num;
        
        if (num >= 1.0e9) {
            item->valueint = 2147483647; // INT_MAX
        } else if (num < -2147483648.0) {
            item->valueint = -2147483648; // INT_MIN (0x80000000)
        } else {
            item->valueint = (int)num;
        }
    }
    return item;
}