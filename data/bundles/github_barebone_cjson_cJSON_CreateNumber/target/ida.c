cJSON *__cdecl cJSON_CreateNumber(double num)
{
  cJSON *item; // [rsp+0h] [rbp-10h]

  item = cJSON_New_Item(&global_hooks);
  if ( item )
  {
    item->type = 8;
    item->valuedouble = num;
    if ( num < 2147483647.0 )
    {
      if ( num > -2147483648.0 )
        item->valueint = (int)num;
      else
        item->valueint = 0x80000000;
    }
    else
    {
      item->valueint = 0x7FFFFFFF;
    }
  }
  return item;
}