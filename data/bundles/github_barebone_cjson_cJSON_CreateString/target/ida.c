cJSON *__cdecl cJSON_CreateString(const char *string)
{
  cJSON *item; // [rsp+8h] [rbp-18h]

  item = cJSON_New_Item(&global_hooks);
  if ( !item )
    return item;
  item->type = 16;
  item->valuestring = (char *)cJSON_strdup((const unsigned __int8 *)string, &global_hooks);
  if ( item->valuestring )
    return item;
  cJSON_Delete(item);
  return 0LL;
}