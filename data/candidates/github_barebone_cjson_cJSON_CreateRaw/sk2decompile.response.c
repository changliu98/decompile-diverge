cJSON *cJSON_CreateRaw(const char *raw) {
  cJSON *item = cJSON_New_Item(&global_hooks);
  if (!item) return NULL;
  item->type = (1 << 7);
  item->valuestring = cJSON_strdup((const unsigned char *)raw, &global_hooks);
  if (!item->valuestring) {
    cJSON_Delete(item);
    return NULL;
  }
  return item;
}