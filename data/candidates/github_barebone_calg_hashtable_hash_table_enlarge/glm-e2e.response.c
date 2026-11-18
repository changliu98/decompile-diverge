int hash_table_enlarge(HashTable *ht) {
    HashTableEntry **old_table = ht->table;
    unsigned int old_table_size = ht->table_size;
    unsigned int old_enlarge_in_progress = ht->enlarge_in_progress;
    
    ht->enlarge_in_progress++;
    
    // Call to an unknown function at offset 0x41 (likely allocates a new table)
    // If it returns 0, it failed, so we revert the state.
    if (some_resize_function(ht) == 0) {
        ht->table = old_table;
        ht->table_size = old_table_size;
        ht->enlarge_in_progress = old_enlarge_in_progress;
        return 0;
    }
    
    // Rehash all existing entries into the new table
    for (unsigned int i = 0; i < old_table_size; i++) {
        HashTableEntry *entry = old_table[i];
        
        // Traverse the linked list of entries in the old bucket
        while (entry != NULL) {
            HashTableEntry *next_entry = entry->next;
            
            // Calculate the new bucket index using the hash function and modulo division
            unsigned int hash = ht->hash_func(entry->key);
            unsigned int bucket = hash % ht->table_size;
            
            // Insert the entry at the head of the new bucket
            entry->next = ht->table[bucket];
            ht->table[bucket] = entry;
            
            // Move to the next entry in the old bucket's chain
            entry = next_entry;
        }
    }
    
    // Free the old table array (the entries themselves were preserved)
    free(old_table);
    
    return 1;
}