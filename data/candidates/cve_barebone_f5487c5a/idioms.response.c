void ReplaceXmpValue(struct StringInfo *str, unsigned long start, unsigned long end, char *value)
{
  char *str_data;
  unsigned long str_length;
  unsigned long value_length;
  unsigned long new_length;
  str_length = string_length(str);
  value_length = string_length_str(value);
  new_length = str_length - (end - start) + value_length;
  if (new_length > str_length)
    string_resize(str, new_length);
  str_data = string_data(str);
  string_copy(&str_data[start + value_length], &str_data[end], str_length - end);
  string_copy(&str_data[start], value, value_length);
  if (new_length < str_length)
  {
    string_resize(str, new_length);
    str_data[new_length] = '\0';
  }
}