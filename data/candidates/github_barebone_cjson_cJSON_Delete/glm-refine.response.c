define cJSON_StringIsConst 0x200

void __cdecl cJSON_Delete(cJSON *item)
{
  cJSON *next;

  while (item)
  {
    next = item->next;

    // If this item is not a reference, recursively delete its children
    if ((item->type & cJSON_IsReference) == 0 && item->child)
    {
      cJSON_Delete(item->child);
    }

    // If this item is not a reference, free its value string
    if ((item->type & cJSON_IsReference) == 0 && item->valuestring)
    {
      global_hooks.deallocate(item->valuestring);
      item->valuestring = NULL;
    }

    // If the key string is not a constant, free it
    if ((item->type & cJSON_StringIsConst) == 0 && item->string)
    {
      global_hooks.deallocate(item->string);
      item->string = NULL;
    }

    // Free the item itself and move on to the next sibling
    global_hooks.deallocate(item);
    item = next;
  }
}