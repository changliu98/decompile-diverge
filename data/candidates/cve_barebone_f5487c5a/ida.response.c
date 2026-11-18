void __cdecl ReplaceXmpValue(StringInfo *profile, size_t start, size_t end, const char *value)
{
  size_t value_length; // [rsp+0h] [rbp-40h]
  size_t new_length; // [rsp+8h] [rbp-38h]
  size_t length; // [rsp+10h] [rbp-30h]
  unsigned __int8 *datum; // [rsp+18h] [rbp-28h]

  length = GetStringInfoLength(profile);
  value_length = strlen(value);
  new_length = value_length + length - (end - start);
  if ( new_length > length )
    SetStringInfoLength(profile, new_length);
  datum = GetStringInfoDatum(profile);
  memmove(&datum[start + value_length], &datum[end], length - end);
  memcpy(&datum[start], value, value_length);
  if ( new_length < length )
  {
    SetStringInfoLength(profile, new_length);
    datum[new_length] = 0;
  }
}