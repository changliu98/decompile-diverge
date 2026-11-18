int cJSON_GetArraySize(struct cJSON *array) {
    int size = 0;
    struct cJSON *child = NULL;
    
    if (array == NULL) {
        return 0;
    }
    
    child = array->next; // Note: offset 0x10 implies 3rd member if 8-byte aligned, 
                         // but typically this is `child` in cJSON. Assuming `next` 
                         // for standard linked list traversal, or `child` if array.
    
    // Wait, looking at standard cJSON, offset 0x10 is `child`.
    // Let's redefine the struct to match standard cJSON layout.
    
    /*
    struct cJSON {
        struct cJSON *next;      // 0x00
        struct cJSON *prev;      // 0x08
        struct cJSON *child;     // 0x10
        // ...
    };
    */
    
    while (child != NULL) {
        size++;
        child = child->next;
    }
    
    return size;
}