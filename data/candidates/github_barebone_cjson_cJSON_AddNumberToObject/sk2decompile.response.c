cJSON *cJSON_AddNumberToObject(cJSON *const object, const char *const name,
                               const double number) {
  cJSON *n = cJSON_CreateNumber(number);
  if (add_item_to_object(object, name, n, &global_hooks, 0)) {
    return n;
  }
  cJSON_Delete(n);
  return NULL;
}