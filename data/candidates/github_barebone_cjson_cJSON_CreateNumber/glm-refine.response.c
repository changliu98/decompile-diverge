cJSON *__cdecl cJSON_CreateNumber(double num)
{
  cJSON *item = cJSON_New_Item(&global_hooks);
  
  if (item)
  {
    item->type = cJSON_Number; // 8
    item->valuedouble = num;
    
    // Clamp the double to fit within a 32-bit signed integer range
    if (num >= INT_MAX)
    {
      item->valueint = INT_MAX;       // 0x7FFFFFFF
    }
    else if (num <= INT_MIN)
    {
      item->valueint = INT_MIN;       // 0x80000000
    }
    else
    {
      item->valueint = (int)num;
    }
  }
  
  return item;
}