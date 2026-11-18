cJSON * cJSON_ParseWithOpts(char *value,char **return_parse_end,cJSON_bool require_null_terminated)

{
  size_t sVar1;
  size_t buffer_length;
  cJSON_bool require_null_terminated_local;
  char **return_parse_end_local;
  char *value_local;
  undefined8 local_10;
  
  if (value == (char *)0x0) {
    local_10 = (cJSON *)0x0;
  }
  else {
    sVar1 = strlen(value);
    local_10 = cJSON_ParseWithLengthOpts(value,sVar1 + 1,return_parse_end,require_null_terminated);
  }
  return local_10;
}