cJSON_bool cJSON_InsertItemInArray(cJSON *array,int which,cJSON *newitem)

{
  cJSON *pcVar1;
  cJSON *after_inserted;
  cJSON *newitem_local;
  int which_local;
  cJSON *array_local;
  cJSON_bool local_c;
  
  if ((which < 0) || (newitem == (cJSON *)0x0)) {
    local_c = 0;
  }
  else {
    pcVar1 = get_array_item(array,(long)which);
    if (pcVar1 == (cJSON *)0x0) {
      local_c = add_item_to_array(array,newitem);
    }
    else if ((pcVar1 == array->child) || (pcVar1->prev != (cJSON *)0x0)) {
      newitem->next = pcVar1;
      newitem->prev = pcVar1->prev;
      pcVar1->prev = newitem;
      if (pcVar1 == array->child) {
        array->child = newitem;
      }
      else {
        newitem->prev->next = newitem;
      }
      local_c = 1;
    }
    else {
      local_c = 0;
    }
  }
  return local_c;
}