Target of call at 0x117

int set_enlarge(struct set *s) {
    struct set_entry **old_buckets = s->buckets;
    unsigned int old_num_buckets = s->num_buckets;
    unsigned int old_num_entries = s->num_entries;

    // Increment the number of entries and attempt to resize/rehash
    s->num_entries++;
    if (set_resize(s) == 0) {
        // Resize failed: revert state and return 0
        s->buckets = old_buckets;
        s->num_buckets = old_num_buckets;
        s->num_entries = old_num_entries;
        return 0;
    }

    // Resize succeeded: rehash existing elements from old buckets into the new ones
    for (unsigned int i = 0; i < old_num_buckets; i++) {
        struct set_entry *entry = old_buckets[i];
        
        // Traverse the linked list in the old bucket
        while (entry != NULL) {
            struct set_entry *next = entry->next;
            
            // Call the set's specific free function on the key
            s->free_func(entry->key);
            
            // Calculate the new bucket index using modulo
            unsigned int new_index = (unsigned int)((uintptr_t)entry % s->num_buckets);
            
            // Relink the entry into the new bucket
            entry->next = s->buckets[new_index];
            s->buckets[new_index] = entry;
            
            // Move to the next entry
            entry = next;
        }
    }

    // Free the array of old bucket pointers
    free_buckets(old_buckets);
    
    return 1;
}