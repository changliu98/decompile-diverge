cJSON * cJSON_AddNumberToObject(cJSON *object,char *name,double number)

{
  cJSON_bool cVar1;
  cJSON *number_item;
  double number_local;
  char *name_local;
  cJSON *object_local;
  cJSON *local_10;
  
  local_10 = cJSON_CreateNumber(number);
  cVar1 = add_item_to_object(object,name,local_10,&global_hooks,0);
  if (cVar1 == 0) {
    cJSON_Delete(local_10);
    local_10 = (cJSON *)0x0;
  }
  return local_10;
}