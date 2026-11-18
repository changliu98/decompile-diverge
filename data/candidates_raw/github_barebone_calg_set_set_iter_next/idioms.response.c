void *set_iterator_next(struct set_iterator *iterator)
{
    struct set *set = iterator->set;
    if (iterator->next_entry == ((void *)0))
        return ((void *)0);
    struct set_entry *next = iterator->next_entry;
    void *data = next->data;
    if (next->next == ((void *)0))
    {
        iterator->next_entry = ((void *)0);
        unsigned int next_chain = iterator->next_chain + 1;
        for (; next_chain < set->table_size; next_chain++)
        {
            if (set->table[next_chain])
            {
                iterator->next_entry = set->table[next_chain];
                break;
            }
        }
        iterator->next_chain = next_chain;
    }
    else
    {
        iterator->next_entry = next->next;
    }
    return data;
}