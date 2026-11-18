SetValue __cdecl set_iter_next(SetIterator *iterator)
{
    if (!iterator->next_entry)
        return 0;

    SetEntry *current_entry = iterator->next_entry;
    SetValue result = current_entry->data;

    if (current_entry->next)
    {
        // Move to the next entry in the current chain
        iterator->next_entry = current_entry->next;
    }
    else
    {
        // End of current chain reached, find the next non-empty chain
        iterator->next_entry = NULL;
        unsigned int chain = iterator->next_chain + 1;
        
        while (chain < iterator->set->table_size)
        {
            if (iterator->set->table[chain])
            {
                iterator->next_entry = iterator->set->table[chain];
                break;
            }
            chain++;
        }
        iterator->next_chain = chain;
    }

    return result;
}