void cJSON_Delete(cJSON *item)

{
  cJSON *pcVar1;
  cJSON *next;
  cJSON *item_local;
  
  item_local = item;
  while (item_local != (cJSON *)0x0) {
    pcVar1 = item_local->next;
    if (((item_local->type & 0x100U) == 0) && (item_local->child != (cJSON *)0x0)) {
      cJSON_Delete(item_local->child);
    }
    if (((item_local->type & 0x100U) == 0) && (item_local->valuestring != (char *)0x0)) {
      (*global_hooks.deallocate)(item_local->valuestring);
      item_local->valuestring = (char *)0x0;
    }
    if (((item_local->type & 0x200U) == 0) && (item_local->string != (char *)0x0)) {
      (*global_hooks.deallocate)(item_local->string);
      item_local->string = (char *)0x0;
    }
    (*global_hooks.deallocate)(item_local);
    item_local = pcVar1;
  }
  return;
}