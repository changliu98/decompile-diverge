char base64_encode_value(char value_in)
{
  if (value_in > 63)
    return '=';
  else
    return base64_encode_value_encoding[value_in];
}