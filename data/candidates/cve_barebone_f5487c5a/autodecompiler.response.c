void ReplaceXmpValue(StringInfo *string_info,const size_t offset,
  const size_t extent,const char *value)
{
  unsigned char
    *base;

  size_t
    length,
    new_extent,
    new_length,
    value_length;

  length=GetStringInfoLength(string_info);
  value_length=strlen(value);
  new_extent=extent-offset;
  new_length=length-new_extent+value_length;
  if (new_length > length)
    SetStringInfoLength(string_info,new_length);
  base=GetStringInfoDatum(string_info);
  memmove(base+offset+value_length,base+extent,length-extent);
  memcpy(base+offset,value,value_length);
  if (new_length < length)
    {
      SetStringInfoLength(string_info,new_length);
      base[new_length]='\0';
    }
}