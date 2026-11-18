cJSON *cJSON_CreateNumber(double num) {
  cJSON *item = cJSON_New_Item(&global_hooks);
  if (item) {
    item->type = 8;
    item->valuedouble = item->valueint = num;
    if (item->valuedouble > 2147483647.0)
      item->valueint = 2147483647;
    else if (item->valuedouble < -2147483648.0)
      item->valueint = -2147483648;
    else
      item->valueint = (int)item->valuedouble;
  }
  return item;
}