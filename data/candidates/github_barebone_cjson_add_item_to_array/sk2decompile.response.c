static BOOL add_item_to_array(cst_item *array, cst_item *item) {
  cst_item *last;
  if (!item || !array || array == item) return 0;
  last = array->last;
  if (!last) {
    array->last = item;
    item->next = item;
    item->prev = 0;
  } else if (last->next) {
    suffix_object(last->next, item);
    array->last->next = item;
  }
  return 1;
}