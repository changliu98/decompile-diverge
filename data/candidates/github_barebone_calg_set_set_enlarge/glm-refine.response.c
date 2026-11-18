int __cdecl set_enlarge(Set *set)
{
    unsigned int i;
    unsigned int index;
    unsigned int old_prime_index;
    unsigned int old_table_size;
    SetEntry **old_table;
    SetEntry *next;
    SetEntry *rover;

    // Save the current state in case reallocation fails
    old_table = set->table;
    old_table_size = set->table_size;
    old_prime_index = set->prime_index;

    // Attempt to scale up the table
    set->prime_index = old_prime_index + 1;
    if (!set_allocate_table(set))
    {
        // Allocation failed: restore the previous state
        set->table = old_table;
        set->table_size = old_table_size;
        set->prime_index = old_prime_index;
        return 0;
    }

    // Allocation succeeded: rehash all existing entries into the new table
    for (i = 0; i < old_table_size; ++i)
    {
        for (rover = old_table[i]; rover != NULL; rover = next)
        {
            next = rover->next;
            
            // Calculate the new bucket index and move the entry
            index = set->hash_func(rover->data) % set->table_size;
            rover->next = set->table[index];
            set->table[index] = rover;
        }
    }

    // Free the old table array
    free(old_table);
    
    return 1;
}