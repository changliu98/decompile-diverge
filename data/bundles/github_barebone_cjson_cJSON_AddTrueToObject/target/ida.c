cJSON *__cdecl cJSON_AddTrueToObject(cJSON *const object, const char *const name)
{
  cJSON *true_item; // [rsp+0h] [rbp-20h]

  true_item = cJSON_CreateTrue();
  if ( add_item_to_object(object, name, true_item, &global_hooks, 0) )
    return true_item;
  cJSON_Delete(true_item);
  return 0LL;
}