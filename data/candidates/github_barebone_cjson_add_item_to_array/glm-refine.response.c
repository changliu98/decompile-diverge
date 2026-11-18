cJSON_bool __cdecl add_item_to_array(cJSON *array, cJSON *item)
{
  cJSON *current_child;

  // Reject invalid inputs or attempts to append an array to itself
  if (item == NULL || array == NULL || array == item)
  {
    return false;
  }

  current_child = array->child;

  if (current_child != NULL)
  {
    // The array already has at least one item.
    if (current_child->prev != NULL)
    {
      // The array has multiple items. Append the new item to the end 
      // (after the current last item, which is tracked by child->prev).
      suffix_object(current_child->prev, item);
      
      // Update the last item pointer of the head node to the newly added item.
      current_child->prev = item;
    }
    // Note: If current_child->prev is NULL, the array has exactly one item.
    // In the original cJSON source, this case is handled by suffix_object 
    // directly, but appears to be missing in this specific decompiled snippet.
  }
  else
  {
    // The array is empty. The new item becomes the first (and only) child.
    array->child = item;
    
    // In cJSON's circular doubly-linked list logic, a single item's 
    // 'prev' pointer points to itself to denote it is also the last item.
    item->prev = item;
    item->next = NULL;
  }

  return true;
}