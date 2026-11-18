int __cdecl cJSON_GetArraySize(const cJSON *array)
{
  int size; // [rsp+0h] [rbp-20h]
  cJSON *child; // [rsp+8h] [rbp-18h]

  size = 0;
  if ( !array )
    return 0;
  for ( child = array->child; child; child = child->next )
    ++size;
  return size;
}