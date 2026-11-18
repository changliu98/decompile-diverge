int cJSON_GetArraySize(const cJSON *array) {
  cJSON *c;
  int i = 0;
  if (!array) return 0;
  for (c = array->child; c; c = c->next) i++;
  return i;
}