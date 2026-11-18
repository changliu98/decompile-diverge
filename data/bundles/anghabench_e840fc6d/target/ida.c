char __cdecl base64_encode_value(char value_in)
{
  if ( value_in <= 63 )
    return base64_encode_value_encoding[value_in];
  else
    return 61;
}