cJSON *cJSON_CreateString(const char *string) {
  cJSON *item = cJSON_New_Item(&global_hooks);
  if (!item) return NULL;
  item->type = (1 << 4);
  item->valuestring = cJSON_strdup((const unsigned char *)string, &global_hooks);
  if (!item->valuestring) {
    cJSON_Delete(item);
    return NULL;
  }
  return item;
}