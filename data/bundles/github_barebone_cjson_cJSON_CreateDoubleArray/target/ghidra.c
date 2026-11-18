cJSON * cJSON_CreateDoubleArray(double *numbers,int count)

{
  cJSON *item;
  cJSON *a;
  cJSON *p;
  cJSON *n;
  size_t i;
  int count_local;
  double *numbers_local;
  cJSON *local_10;
  
  n = (cJSON *)0x0;
  if ((count < 0) || (numbers == (double *)0x0)) {
    local_10 = (cJSON *)0x0;
  }
  else {
    local_10 = cJSON_CreateArray();
    for (i = 0; local_10 != (cJSON *)0x0 && i < (ulong)(long)count; i = i + 1) {
      item = cJSON_CreateNumber(numbers[i]);
      if (item == (cJSON *)0x0) {
        cJSON_Delete(local_10);
        return (cJSON *)0x0;
      }
      if (i == 0) {
        local_10->child = item;
      }
      else {
        suffix_object(n,item);
      }
      n = item;
    }
    if ((local_10 != (cJSON *)0x0) && (local_10->child != (cJSON *)0x0)) {
      local_10->child->prev = n;
    }
  }
  return local_10;
}