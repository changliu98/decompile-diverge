static cJSON *get_object_item(const cJSON *const object, const char *const name,
                              const cJSON_bool case_sensitive) {
  cJSON *item;
  if (!object || !name) {
    return NULL;
  }
  item = object->child;
  if (case_sensitive) {
    while (item && strcmp(name, item->string)) {
      item = item->next;
    }
  } else {
    while (item && case_insensitive_strcmp((const unsigned char *)name,
                                           (const unsigned char *)item->string)) {
      item = item->next;
    }
  }
  return item;
}