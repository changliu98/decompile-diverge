int cJSON_GetArraySize(cJSON *array)

{
  size_t size;
  cJSON *child;
  cJSON *array_local;
  int local_c;
  
  size = 0;
  if (array == (cJSON *)0x0) {
    local_c = 0;
  }
  else {
    for (child = array->child; child != (cJSON *)0x0; child = child->next) {
      size = size + 1;
    }
    local_c = (int)size;
  }
  return local_c;
}