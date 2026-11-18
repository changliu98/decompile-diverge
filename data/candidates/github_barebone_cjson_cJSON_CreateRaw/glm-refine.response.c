cJSON *__cdecl cJSON_CreateRaw(const char *raw)
{
  cJSON *item = cJSON_New_Item(&global_hooks);
  
  if (item == NULL) {
    return NULL;
  }
  
  item->type = cJSON_Raw; // Assuming 128 corresponds to cJSON_Raw based on cJSON's source code
  item->valuestring = cJSON_strdup(raw, &global_hooks);
  
  if (item->valuestring != NULL) {
    return item;
  }
  
  cJSON_Delete(item);
  return NULL;
}