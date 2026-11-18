cJSON *__cdecl cJSON_CreateString(const char *string)
{
  cJSON *item = cJSON_New_Item(&global_hooks);
  
  if (!item)
    return NULL;

  item->type = cJSON_String;
  item->valuestring = cJSON_strdup(string, &global_hooks);
  
  if (item->valuestring)
    return item;

  cJSON_Delete(item);
  return NULL;
}