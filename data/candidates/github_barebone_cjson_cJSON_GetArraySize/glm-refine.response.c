int __cdecl cJSON_GetArraySize(const cJSON *array)
{
  if (!array || !array->child)
    return 0;

  int size = 0;
  for (cJSON *child = array->child; child; child = child->next)
    ++size;

  return size;
}