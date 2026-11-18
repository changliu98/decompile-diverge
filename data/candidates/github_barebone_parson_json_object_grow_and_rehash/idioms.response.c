int json_object_grow_and_rehash(struct json_object *source, struct json_object *target)
{
  struct json_object *src = source;
  struct json_object *dst = target;
  struct json_value *value = ((void *)0);
  unsigned int i;
  if (src->cell_capacity * 2 > 16)
    json_object_init(&dst->value, src->cell_capacity * 2);
  else
    json_object_init(&dst->value, 16);
  if (dst->value == ((void *)0))
    return -1;
  value = json_value_copy(&src->value);
  dst->value.value.object = value;
  for (i = 0; i < src->count; i++) {
    struct json_value *src_value = src->values[i];
    if (json_object_set(&dst->value, src->names[i], src_value)) {
      json_value_free(&dst->value, ((void *)0), ((void *)0));
      return -1;
    }
    src_value->parent = value;
  }
  json_value_free(&src->value, ((void *)0), ((void *)0));
  json_object_copy(&src->value, &dst->value, sizeof(json_object_t));
  return 0;
}