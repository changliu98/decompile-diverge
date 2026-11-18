cJSON *cJSON_AddTrueToObject(cJSON *const object, const char *const name) {
  cJSON *true_item = cJSON_CreateTrue();
  if (add_item_to_object(object, name, true_item, &global_hooks, 0)) {
    return true_item;
  }
  cJSON_Delete(true_item);
  return NULL;
}