int json_object_grow_and_rehash(JSON_Object *object) {
    char *key = NULL;
    JSON_Value *value = NULL;
    size_t i = 0;
    int res;
    HashTable new_hash_table;
    size_t new_capacity;

    // Determine the new hash table capacity
    if (object->capacity * 2 > 16) {
        new_capacity = object->capacity * 2;
    } else {
        new_capacity = 16;
    }

    // Initialize the new hash table
    res = hash_table_init(&new_hash_table, new_capacity);
    if (res != 0) {
        return -1;
    }

    // Rehash all existing key-value pairs into the new hash table
    for (i = 0; i < object->count; i++) {
        key = object->keys[i];
        value = object->values[i];

        res = hash_table_put(&new_hash_table, key, value);
        if (res != 0) {
            // hash_table_deinit(&new_hash_table, 0, 0);
            // Using memset to clear the local hash table struct on failure as seen in assembly
            memset(&new_hash_table, 0, sizeof(HashTable)); 
            return -1;
        }
        
        // Link the newly inserted hash table cell back to the array index
        // (This is a common Parson optimization to allow O(1) removals from the hash table)
        *((char **)value) = key; 
    }

    // Clear the old hash table associated with the object
    hash_table_clear(object, 0, 0);

    // Replace the object's old hash table with the newly populated one
    memcpy(&object->hash_table, &new_hash_table, 0x48); // 72 bytes copied

    return 0;
}