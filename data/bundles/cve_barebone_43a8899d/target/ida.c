cJSON *__cdecl get_object_item(const cJSON *const object, const char *const name, const cJSON_bool case_sensitive)
{
  bool v4; // [rsp+6h] [rbp-2Ah]
  bool v5; // [rsp+7h] [rbp-29h]
  cJSON *current_element; // [rsp+8h] [rbp-28h]

  if ( !object || !name )
    return 0LL;
  current_element = object->child;
  if ( case_sensitive )
  {
    while ( 1 )
    {
      v5 = 0;
      if ( current_element )
        v5 = strcmp(name, current_element->string) != 0;
      if ( !v5 )
        break;
      current_element = current_element->next;
    }
  }
  else
  {
    while ( 1 )
    {
      v4 = 0;
      if ( current_element )
        v4 = case_insensitive_strcmp((const unsigned __int8 *)name, (const unsigned __int8 *)current_element->string) != 0;
      if ( !v4 )
        break;
      current_element = current_element->next;
    }
  }
  return current_element;
}