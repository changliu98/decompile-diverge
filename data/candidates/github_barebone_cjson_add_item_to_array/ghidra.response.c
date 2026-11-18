cJSON_bool add_item_to_array(cJSON *array,cJSON *item)

{
  cJSON *pcVar1;
  cJSON *child;
  cJSON *item_local;
  cJSON *array_local;
  cJSON_bool local_c;
  
  if (((item == (cJSON *)0x0) || (array == (cJSON *)0x0)) || (array == item)) {
    local_c = 0;
  }
  else {
    pcVar1 = array->child;
    if (pcVar1 == (cJSON *)0x0) {
      array->child = item;
      item->prev = item;
      item->next = (cJSON *)0x0;
    }
    else if (pcVar1->prev != (cJSON *)0x0) {
      suffix_object(pcVar1->prev,item);
      array->child->prev = item;
    }
    local_c = 1;
  }
  return local_c;
}