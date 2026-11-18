int __cdecl hash_table_enlarge(HashTable *hash_table)
{
    unsigned int i;
    unsigned int new_index;
    HashTableEntry *next_entry;
    HashTableEntry *current_entry;
    unsigned int old_prime_index;
    unsigned int old_table_size;
    HashTableEntry **old_table;

    // Save the current state of the hash table
    old_table = hash_table->table;
    old_table_size = hash_table->table_size;
    old_prime_index = hash_table->prime_index;

    // Attempt to scale up the table by moving to the next prime size
    hash_table->prime_index = old_prime_index + 1;

    if (hash_table_allocate_table(hash_table))
    {
        // Rehash all existing entries into the newly allocated table
        for (i = 0; i < old_table_size; ++i)
        {
            for (current_entry = old_table[i]; current_entry != NULL; current_entry = next_entry)
            {
                next_entry = current_entry->next;
                
                // Calculate the new bucket index
                new_index = hash_table->hash_func(current_entry->pair.key) % hash_table->table_size;
                
                // Insert the entry at the head of the new bucket
                current_entry->next = hash_table->table[new_index];
                hash_table->table[new_index] = current_entry;
            }
        }
        
        // Free the old table array and return success
        free(old_table);
        return 1;
    }
    else
    {
        // Allocation failed: restore the original table state and return failure
        hash_table->table = old_table;
        hash_table->table_size = old_table_size;
        hash_table->prime_index = old_prime_index;
        return 0;
    }
}