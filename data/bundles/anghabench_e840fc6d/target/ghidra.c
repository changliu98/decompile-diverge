char base64_encode_value(char value_in)

{
  char value_in_local;
  char local_9;
  
  if (value_in < '@') {
    local_9 = base64_encode_value::encoding[(int)value_in];
  }
  else {
    local_9 = '=';
  }
  return local_9;
}