cJSON *cJSON_AddRawToObject(cJSON *const object, const char *const name,
                            const char *const raw) {
  cJSON *node = cJSON_CreateRaw(raw);
  if (add_item_to_object(object, name, node, &global_hooks, 0)) {
    return node;
  }
  cJSON_Delete(node);
  return NULL;
}