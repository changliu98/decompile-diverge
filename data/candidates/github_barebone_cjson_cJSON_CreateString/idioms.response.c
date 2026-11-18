struct cJSON *cJSON_CreateString(char *string)
{
 struct cJSON *item = cJSON_New_Item();
 if (!item) return item;
 item->type = cJSON_String;
 item->valuestring = cJSON_strdup(string);
 if (!item->valuestring)
 {
  cJSON_Delete(item);
  return ((void *)0);
 }
 return item;
}