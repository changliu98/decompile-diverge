char base64_encode_value(char value_in)
{
  char value_out;
  if (value_in >= 64)
    value_out = '=';
  else
    value_out = encoding[value_in];
  return value_out;
}