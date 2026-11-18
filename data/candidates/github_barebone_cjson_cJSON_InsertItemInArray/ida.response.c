cJSON_bool __cdecl cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem)
{
  cJSON *after_inserted; // [rsp+8h] [rbp-28h]

  if ( which < 0 || !newitem )
    return 0;
  after_inserted = get_array_item(array, which);
  if ( !after_inserted )
    return add_item_to_array(array, newitem);
  if ( after_inserted != array->child && !after_inserted->prev )
    return 0;
  newitem->next = after_inserted;
  newitem->prev = after_inserted->prev;
  after_inserted->prev = newitem;
  if ( after_inserted == array->child )
    array->child = newitem;
  else
    newitem->prev->next = newitem;
  return 1;
}