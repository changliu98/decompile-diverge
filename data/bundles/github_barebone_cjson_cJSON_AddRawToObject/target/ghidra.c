cJSON * cJSON_AddRawToObject(cJSON *object,char *name,char *raw)

{
  cJSON_bool cVar1;
  cJSON *raw_item;
  char *raw_local;
  char *name_local;
  cJSON *object_local;
  cJSON *local_10;
  
  local_10 = cJSON_CreateRaw(raw);
  cVar1 = add_item_to_object(object,name,local_10,&global_hooks,0);
  if (cVar1 == 0) {
    cJSON_Delete(local_10);
    local_10 = (cJSON *)0x0;
  }
  return local_10;
}