void __cdecl cJSON_Delete(cJSON *item)
{
  cJSON *next; // [rsp+0h] [rbp-10h]

  while ( item )
  {
    next = item->next;
    if ( (item->type & 0x100) == 0 && item->child )
      cJSON_Delete(item->child);
    if ( (item->type & 0x100) == 0 && item->valuestring )
    {
      global_hooks.deallocate(item->valuestring);
      item->valuestring = 0LL;
    }
    if ( (item->type & 0x200) == 0 )
    {
      if ( item->string )
      {
        global_hooks.deallocate(item->string);
        item->string = 0LL;
      }
    }
    global_hooks.deallocate(item);
    item = next;
  }
}