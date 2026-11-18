char * cJSON_SetValuestring(cJSON *object,char *valuestring)

{
  size_t sVar1;
  size_t sVar2;
  size_t v2_len;
  size_t v1_len;
  char *copy;
  char *valuestring_local;
  cJSON *object_local;
  uchar *local_10;
  
  if (((object == (cJSON *)0x0) || ((object->type & 0x10U) == 0)) || ((object->type & 0x100U) != 0))
  {
    local_10 = (uchar *)0x0;
  }
  else if ((object->valuestring == (char *)0x0) || (valuestring == (char *)0x0)) {
    local_10 = (uchar *)0x0;
  }
  else {
    sVar1 = strlen(valuestring);
    sVar2 = strlen(object->valuestring);
    if (sVar2 < sVar1) {
      local_10 = cJSON_strdup((uchar *)valuestring,&global_hooks);
      if (local_10 == (uchar *)0x0) {
        local_10 = (uchar *)0x0;
      }
      else {
        if (object->valuestring != (char *)0x0) {
          cJSON_free(object->valuestring);
        }
        object->valuestring = (char *)local_10;
      }
    }
    else if ((valuestring + sVar1 < object->valuestring) ||
            (object->valuestring + sVar2 < valuestring)) {
      strcpy(object->valuestring,valuestring);
      local_10 = (uchar *)object->valuestring;
    }
    else {
      local_10 = (uchar *)0x0;
    }
  }
  return (char *)local_10;
}