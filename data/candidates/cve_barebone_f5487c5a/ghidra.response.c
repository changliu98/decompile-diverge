void ReplaceXmpValue(StringInfo *profile,size_t start,size_t end,char *value)

{
  size_t sVar1;
  size_t __n;
  ulong length_00;
  uchar *puVar2;
  size_t value_length;
  size_t new_length;
  size_t length;
  char *datum;
  char *value_local;
  size_t end_local;
  size_t start_local;
  StringInfo *profile_local;
  
  sVar1 = GetStringInfoLength(profile);
  __n = strlen(value);
  length_00 = (sVar1 - (end - start)) + __n;
  if (sVar1 < length_00) {
    SetStringInfoLength(profile,length_00);
  }
  puVar2 = GetStringInfoDatum(profile);
  memmove(puVar2 + __n + start,puVar2 + end,sVar1 - end);
  memcpy(puVar2 + start,value,__n);
  if (length_00 < sVar1) {
    SetStringInfoLength(profile,length_00);
    puVar2[length_00] = '\0';
  }
  return;
}