static int json_array_resize(struct json_array *array, unsigned long new_capacity)
{
  struct json_value **new_items = ((void *)0);
  if (new_capacity < 1)
    return -1;
  new_items = (struct json_value **)parson_malloc(new_capacity * sizeof(struct json_value *));
  if (new_items == ((void *)0))
    return -1;
  if (array->items != ((void *)0) && array->count > 0)
    json_array_copy(new_items, array->items, array->count * sizeof(struct json_value *));
  parson_free(array->items);
  array->items = new_items;
  array->capacity = new_capacity;
  return 0;
}