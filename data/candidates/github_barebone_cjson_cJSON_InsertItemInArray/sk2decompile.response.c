cJSON_bool cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem) {
  cJSON *c;
  if (which < 0 || !newitem) return 0;
  c = get_array_item(array, which);
  if (!c) return add_item_to_array(array, newitem);
  if (c != array->child && !c->next) return 0;
  newitem->prev = c;
  newitem->next = c->next;
  c->next = newitem;
  if (c == array->child)
    array->child = newitem;
  else
    newitem->next->prev = newitem;
  return 1;
}