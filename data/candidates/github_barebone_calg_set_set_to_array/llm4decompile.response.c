SetValue *set_to_array(Set *set){
    SetValue *array;
    unsigned int i, array_counter=0;
    SetEntry *rover;

    array = (SetValue *)malloc(set->entries * sizeof(SetValue));
    if(array == NULL) return NULL;

    for(i=0; i<set->table_size; i++){
        for(rover=set->table[i]; rover!=NULL; rover=rover->next){
            array[array_counter++] = rover->data;
        }
    }

    return array;
}