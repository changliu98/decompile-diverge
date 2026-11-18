cJSON * cJSON_CreateString(char *string)

{
  uchar *puVar1;
  cJSON *item;
  char *string_local;
  cJSON *local_10;
  
  local_10 = cJSON_New_Item(&global_hooks);
  if (local_10 != (cJSON *)0x0) {
    local_10->type = 0x10;
    puVar1 = cJSON_strdup((uchar *)string,&global_hooks);
    local_10->valuestring = (char *)puVar1;
    if (local_10->valuestring == (char *)0x0) {
      cJSON_Delete(local_10);
      local_10 = (cJSON *)0x0;
    }
  }
  return local_10;
}