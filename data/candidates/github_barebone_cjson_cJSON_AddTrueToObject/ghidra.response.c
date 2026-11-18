cJSON * cJSON_AddTrueToObject(cJSON *object,char *name)

{
  cJSON_bool cVar1;
  cJSON *true_item;
  char *name_local;
  cJSON *object_local;
  cJSON *local_10;
  
  local_10 = cJSON_CreateTrue();
  cVar1 = add_item_to_object(object,name,local_10,&global_hooks,0);
  if (cVar1 == 0) {
    cJSON_Delete(local_10);
    local_10 = (cJSON *)0x0;
  }
  return local_10;
}