cJSON_bool __cdecl cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem)
{
  cJSON *insertion_point;

  // Validate inputs: index cannot be negative and the new item must exist
  if (which < 0 || !newitem)
    return 0;

  // Find the item currently at the target index
  insertion_point = get_array_item(array, which);

  // If the index is out of bounds (beyond the end of the array), append to the end
  if (!insertion_point)
    return add_item_to_array(array, newitem);

  // Sanity check: ensure the target item is properly linked in the list
  if (insertion_point != array->child && !insertion_point->prev)
    return 0;

  // Link the new item into the position before the insertion point
  newitem->next = insertion_point;
  newitem->prev = insertion_point->prev;
  insertion_point->prev = newitem;

  // Update the head of the list if inserting at the very beginning, 
  // otherwise link the preceding item's 'next' pointer to the new item
  if (insertion_point == array->child)
    array->child = newitem;
  else
    newitem->prev->next = newitem;

  return 1;
}