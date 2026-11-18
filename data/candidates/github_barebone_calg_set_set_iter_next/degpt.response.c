SetValue set_iter_next(SetIterator *iter)
{
    // Get the current entry to be returned
    SetEntry *entry = iter->next_entry;
    
    // If there are no more entries, return a null SetValue
    if (entry == NULL) {
        return (SetValue)0x0;
    }

    // Store the data from the current entry to return later
    SetValue value = entry->data;

    // If the current entry has no next sibling in the chain,
    // move to the next non-empty chain in the hash table
    if (entry->next == NULL) {
        Set *hash_set = iter->set;
        uint bucket_index = iter->next_chain;
        do {
            bucket_index++;
            // If we've exceeded the table size, stop searching
            if (hash_set->table_size <= bucket_index) {
                break;
            }
        } while (hash_set->table[bucket_index] == NULL);

        // Update the iterator to point to the first entry in the new chain
        iter->next_entry = hash_set->table[bucket_index];
        iter->next_chain = bucket_index;
    } else {
        // Otherwise, move to the next entry in the same chain
        iter->next_entry = entry->next;
    }

    // Return the data from the current entry
    return value;
}