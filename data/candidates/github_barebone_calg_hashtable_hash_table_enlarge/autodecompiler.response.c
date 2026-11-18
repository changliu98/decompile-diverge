int hash_table_enlarge(hash_table_t *table)
{
    hash_table_entry_t **old_table;
    unsigned int old_table_size, old_prime_index;
    unsigned int i, index;
    hash_table_entry_t *rover, *next, *pair;
    int result;

    old_table = table->table;
    old_table_size = table->table_size;
    old_prime_index = table->prime_index;

    table->prime_index++;
    if (!hash_table_allocate_table(table)) {
        table->table = old_table;
        table->table_size = old_table_size;
        table->prime_index = old_prime_index;
        result = 0;
    } else {
        for (i = 0; i < old_table_size; i++) {
            rover = old_table[i];
            while (rover != NULL) {
                next = rover->next;
                pair = (hash_table_entry_t *)rover;
                index = (*table->hash_func)(pair->key) % table->table_size;
                rover->next = table->table[index];
                table->table[index] = rover;
                rover = next;
            }
        }
        free(old_table);
        result = 1;
    }

    return result;
}