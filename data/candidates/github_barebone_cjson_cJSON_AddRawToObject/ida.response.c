cJSON *__cdecl cJSON_AddRawToObject(cJSON *const object, const char *const name, const char *const raw)
{
  cJSON *raw_item; // [rsp+8h] [rbp-28h]

  raw_item = cJSON_CreateRaw(raw);
  if ( add_item_to_object(object, name, raw_item, &global_hooks, 0) )
    return raw_item;
  cJSON_Delete(raw_item);
  return 0LL;
}