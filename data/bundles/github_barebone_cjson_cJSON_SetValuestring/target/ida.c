char *__cdecl cJSON_SetValuestring(cJSON *object, const char *valuestring)
{
  size_t v2_len; // [rsp+0h] [rbp-30h]
  size_t v1_len; // [rsp+8h] [rbp-28h]
  char *copy; // [rsp+10h] [rbp-20h]

  if ( !object || (object->type & 0x10) == 0 || (object->type & 0x100) != 0 )
    return 0LL;
  if ( !object->valuestring || !valuestring )
    return 0LL;
  v1_len = strlen(valuestring);
  v2_len = strlen(object->valuestring);
  if ( v1_len > v2_len )
  {
    copy = (char *)cJSON_strdup((const unsigned __int8 *)valuestring, &global_hooks);
    if ( copy )
    {
      if ( object->valuestring )
        cJSON_free(object->valuestring);
      object->valuestring = copy;
      return copy;
    }
    else
    {
      return 0LL;
    }
  }
  else if ( &valuestring[v1_len] < object->valuestring || &object->valuestring[v2_len] < valuestring )
  {
    strcpy(object->valuestring, valuestring);
    return object->valuestring;
  }
  else
  {
    return 0LL;
  }
}