cJSON *__cdecl cJSON_AddNumberToObject(cJSON *const object, const char *const name, const double number)
{
  cJSON *number_item; // [rsp+8h] [rbp-28h]

  number_item = cJSON_CreateNumber(number);
  if ( add_item_to_object(object, name, number_item, &global_hooks, 0) )
    return number_item;
  cJSON_Delete(number_item);
  return 0LL;
}