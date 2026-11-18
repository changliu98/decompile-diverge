cJSON *cJSON_AddTrueToObject(cJSON *const object, const char *const name)
{
  cJSON *new_item = cJSON_CreateTrue();

  if (!add_item_to_object(object, name, new_item, &global_hooks, 0)) {
    cJSON_Delete(new_item);
    return NULL;
  }

  return new_item;
}