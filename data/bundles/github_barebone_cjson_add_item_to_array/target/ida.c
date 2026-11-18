cJSON_bool __cdecl add_item_to_array(cJSON *array, cJSON *item)
{
  cJSON *child; // [rsp+0h] [rbp-20h]

  if ( !item || !array || array == item )
    return 0;
  child = array->child;
  if ( child )
  {
    if ( child->prev )
    {
      suffix_object(child->prev, item);
      array->child->prev = item;
    }
  }
  else
  {
    array->child = item;
    item->prev = item;
    item->next = 0LL;
  }
  return 1;
}